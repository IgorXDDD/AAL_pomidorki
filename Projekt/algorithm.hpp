#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#include "generator.hpp"
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;

class Algorithm
{
private:
    int k;
    int n;
    int h;
    int w;
    Generator::field_type field;
    int max(int a,int b);
    int min(int a, int b);
public:
    Algorithm(int k, int n, int h, int w);
    void set_field(Generator::field_type field);
    auto run();
    void setparams(int n, int k, int h, int w);
    void setparams(int k, int h, int w);
};

Algorithm::max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}
Algorithm::min(int a, int b)
{
    if(a<b)
        return a;
    return b;
}


Algorithm::Algorithm(int n, int k, int h, int w) : k(k), h(h), w(w), n(n)
{}


void Algorithm::set_field(Generator::field_type field)
{
    this->field = field;
}

void Algorithm::setparams(int n, int k, int h, int w)
{
    this->k=k;
    this->n=n;
    this->w=w;
    this->h=h;
}
void Algorithm::setparams(int k, int h, int w)
{
    this->k=k;
    this->w=w;
    this->h=h;
}

auto Algorithm::run()
{
    map<uint16_t,vector<uint16_t>> nzpd;
    //wrzucamy do wektora wszystkie
    for(auto i = field.begin(); i != field.end(); i++)
        nzpd[i->first].push_back(i->second);

    pair<uint16_t,uint16_t> maxloc;
    int maxsum=0;

    auto start = high_resolution_clock::now();

    for(auto i = field.begin(); i != field.end(); i++)
    {
        vector<uint16_t> pointsright;
        //16
        pointsright.resize(n);

        for(int j=max(i->first-(h-1), 0); j<min(i->first+h, n); j++)
        {
            int len=0;
            //zliczamy te, ktore rozpoczynajac od punktu roboczego, bylyby pokryte przez plachte
            if(nzpd.find(j) == nzpd.end())
            {
                //nie istnieje
            }
            else
            {
                for(int k=0; k<nzpd[j].size(); k++)
                {
                    if((i->second <= nzpd[j].at(k)) && (nzpd[j].at(k) <= (i->second+(w-1))))
                    {
                        len++;
                    }
                }
            }
            pointsright[j] = len;
        }
        //22
        for(int j = (1-h); j<h; j++)
        {
            int sum=0;
            int count=0;
            for(int k = max(i->first+j,0); k<min(i->first+j+h,n); k++)
            {
                sum+=pointsright.at(k);
                count++;
            }

            if(sum>maxsum)
            {
                maxsum=sum;
                maxloc.first=i->first;
                maxloc.second=i->second;
            }
        }

        //korekta jezeli poza granicami
        maxloc.first = min(n-h,maxloc.first);
        maxloc.second = min(n-w,maxloc.second);
    }
    auto stop = high_resolution_clock::now();
    cout<<"\nZnaleziono max dla: "<<maxloc.first<<","<<maxloc.second<<" i  wynosi: "<<maxsum<<endl;
    auto duration = duration_cast<microseconds>(stop-start);
    return duration;
}


#endif