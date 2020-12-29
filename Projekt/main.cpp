#include <iostream>
#include "generator.hpp"
#include <regex>
#include <map>

#include <unistd.h>



#define SCENARIO_DEFAULT 0
#define SCENARIO_ONE 1
#define SCENARIO_TWO 2
#define FIELD_SIZE 60000
using namespace std;

void switch_scenario(int scenario);
void handle_argc(char **argc,int argv);
void alg(const Generator::field_type & field,int n,int h, int w);

int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}
int min(int a, int b)
{
    if(a<b)
        return a;
    return b;
}

int main(int argv, char* argc[])
{

    Generator gen(30000,14002);
    gen.generate();
    Generator::field_type pole;
    pole = gen.get_field();
    //handle_argc(argc,argv);
    //gen.print_cords();
    alg(pole,30000,1000,1000);
 
    return 0;
}

void switch_scenario(int scenario)
{
    switch (scenario)
    {
    case SCENARIO_DEFAULT:
        /* code */
        break;
    case SCENARIO_ONE:
        /* code */
        break;
    case SCENARIO_TWO:
        /* code */
        break;
    default:
        break;
    }
}


void handle_argc(char **argc,int argv)
{
    string arguments;
    for(int i=1;i<argv;i++)
    {
        arguments+=argc[i];
        arguments+=" ";
    }

    smatch match;
    //m1 = podajemy standardowe wejscie i wywalamy na stdout
    if(regex_search(arguments,match,regex("-m1\\s+")))
    {
        cout<<"znaleziono -m1\n";
    }

    //m2 = tutaj podajemy 
    else if (regex_search(arguments,match,regex("-m2\\s+-k(\\d{1,6})\\s+")))
    {
        cout<<"znaleziono -m2: "<<match.str(0)<<endl;
        cout<<match.str(1)<<endl;
    }
    else if (regex_search(arguments,match,regex("-m3\\s+-k(\\d{1,6})\\s+")))
    {
        cout<<"znaleziono -m3: "<<match.str(0)<<endl;
        cout<<match.str(1)<<endl;
    }
    else
    {
        cout<<"NIE ZNALEZIONO\n";
    }
    
}

void alg(const Generator::field_type &field,int n, int h, int w)
{
    map<uint16_t,vector<uint16_t>> nzpd;
    //wrzucamy do wektora wszystkie
    for(auto i = field.begin(); i != field.end(); i++)
        nzpd[i->first].push_back(i->second);

    pair<uint16_t,uint16_t> maxloc;
    int maxsum=0,thissum=0;
    //cout<<"DUPA"<<endl;
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
            for(int k = max(i->first+j,0); k<min(i->first+j+h,n); k++)// 300=n
            {
                // cout<<"CHCEMY UZYC: "<<k<<endl;
                sum+=pointsright.at(k);
                count++;
            }
            //cout<<"PRZESZLO: "<<count<<" RAZY\n";

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
    cout<<"\nZnaleziono max dla: "<<maxloc.first<<","<<maxloc.second<<" i  wynosi: "<<maxsum<<endl;
}
