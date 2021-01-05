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
    int best_sum;
    pair<int,int> bestloc;
    pair<int,int> h_w_order;
    Generator::field_type field;
    int max(int a,int b);
    int min(int a, int b);
    std::chrono::microseconds run_instance();
    void swap_h_w();
public:
    Algorithm(int k, int n, int h, int w);
    void set_field(Generator::field_type field);
    void set_sheet(int h, int w);
    void setparams(int n, int k, int h, int w);
    void setparams(int k, int h, int w);
    auto run();
    //wydobywacze
    pair<int,int> get_location();
    pair<int,int> get_sizes();
    int get_count();
};

int Algorithm::max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}
int Algorithm::min(int a, int b)
{
    if(a<b)
        return a;
    return b;
}
void Algorithm::swap_h_w()
{
    int tmp=h;
    h=w;
    w=tmp;
}
Algorithm::Algorithm(int n, int k, int h, int w) : k(k), h(h), w(w), n(n)
{
    best_sum=0;
}

void Algorithm::set_field(Generator::field_type field)
{
    this->field = field;
}

void Algorithm::set_sheet(int h, int w)

{
    this->h = h;
    this->w = w;
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

std::chrono::microseconds Algorithm::run_instance()
{
    map<int,vector<int>> nzpd;
    //wrzucamy do wektora wszystkie
    for(auto i = field.begin(); i != field.end(); i++)
        nzpd[i->first].push_back(i->second);

    pair<int,int> maxloc;
    int maxsum=0;

    auto start = high_resolution_clock::now();

    //przechodzimy po kazdym z punktow
    // zlozonosc * k
    for(auto i = field.begin(); i != field.end(); i++)
    {
        vector<int> pointsdown;
        //16
        pointsdown.resize(n);


        //przechodzimy po sasiedztwie punktu roboczego
        // zlozonosc * h
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
                //przechodzimy w dol po kazdym z punktow
                //pesymistycznie przejdziemy w razy
                // zlozonosc *w
                for(int k=0; k<nzpd[j].size(); k++)
                {
                    if((i->second <= nzpd[j].at(k)) && (nzpd[j].at(k) <= (i->second+w)))
                    {
                        len++;
                    }
                }
            }
            pointsdown[j] = len;
        }
        for(int j = (1-h); j<h; j++)
        {
            int sum=0;
            for(int k = max(i->first+j,0); k<min(i->first+j+h+1,n); k++)
            {
                sum+=pointsdown.at(k);
            }

            if(sum>maxsum)
            {
                maxsum=sum;
                maxloc.first=i->first+j;
                maxloc.second=i->second;
            }
        }

        //korekta jezeli poza granicami
        maxloc.first = min(n-h,maxloc.first);
        maxloc.second = min(n-w,maxloc.second);
    }

    //jezeli dane wykonanie dało najlepszy wynik to zapisz ten wynik
    //przyda się on później kiedy będziemy chcieli wydobyć najlepszy wynik
    if(maxsum>best_sum)
    {
        best_sum=maxsum;
        bestloc.first=maxloc.first;
        bestloc.second=maxloc.second;
        h_w_order.first=h;
        h_w_order.second=w;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    return duration;
}

auto Algorithm::run()
{
    best_sum=0;
    auto duration = run_instance().count();
    if(h!=w)
    {
        swap_h_w();
        duration +=run_instance().count();
    }
    return duration;
}

pair<int,int> Algorithm::get_location()
{
    return bestloc;
}

pair<int,int> Algorithm::get_sizes()
{
    return h_w_order;
}

int Algorithm::get_count()
{
    return best_sum;
}

#endif