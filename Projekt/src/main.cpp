#include <iostream>

#include <regex>
#include "algorithm.hpp"
#include "generator.hpp"
#include "naive.hpp"

#define FIELD_SIZE 60000
#define MAX_TOMATOE_COUNT 15000
#define MAX_HEIGHT_WIDTH 10000

using namespace std;
int handle_argc(int argv, char **argc);
int scenario_m1(string arguments);
int scenario_m2(string arguments);
int scenario_m3(string arguments);
int scenario_m4(string arguments);

int main(int argv, char* argc[])
{
    handle_argc(argv,argc);
    return 0;
}

int handle_argc(int argv, char **argc)
{
    string arguments;
    // sklejamy ze soba argumenty

    for(int i=1;i<argv;i++)
    {
        arguments+=argc[i];
        arguments+=" ";
    }

    smatch match;
    if(regex_search(arguments,match,regex("-m1")))
        return scenario_m1(arguments);
    else if (regex_search(arguments,match,regex("-m2")))
        return scenario_m2(arguments);    
    else if (regex_search(arguments,match,regex("-m3")))
        return scenario_m3(arguments);
    else if (regex_search(arguments,match,regex("-m4")))
        return scenario_m4(arguments);
    else
    {
        cout<<"nie wykryto zadnego z trybow uruchomien\n";
        return -1;
    }
}
/*
    ---------------------m1---------------------
    pobieramy informacje o instancji problemu ze 
    standardowego wejscia i ją rozwiazujemy
    */
int scenario_m1(string arguments)
{
    smatch match;    
    int h,k,n,w;
    cin>>h;
    cin>>w;
    cin>>n;
    cin>>k;

    int x,y;

    Field field;
    field.set_size(n);
    for(int i=0;i<k;i++)
    {
        cin>>x;
        cin>>y;
        field.add(make_pair(x,y));
    }
    // moze jeszcze byc taka sytuacja ze uzytkownik wybiera wlasne h oraz w
    if(regex_search(arguments,match,regex("-h(\\d{1,6})")))
        h=atoi(match.str(1).c_str());
    if(regex_search(arguments,match,regex("-w(\\d{1,6})")))
        w=atoi(match.str(1).c_str());

    Algorithm tomatoe_search(k,h,w);
    tomatoe_search.set_field(field);


    cout<<"\tNasz algorytm znalazl w: "<<tomatoe_search.run()/1000000.0<<" sekund"<<endl;
    cout<<"\tnajlepszy wynik:\n";
    cout<<"\t"<<tomatoe_search.get_count()<<" krzakow przykrytych dla punktu: ("<<tomatoe_search.get_location().first<<", "<<tomatoe_search.get_location().second<<")"<<endl;
    cout<<"\tWymiary plachty: "<<tomatoe_search.get_sizes().first<<" x "<<tomatoe_search.get_sizes().second<<endl;
    return 0;
}
/*
---------------------m2---------------------
generujemy instancje problemu i ją rozwiazujemy
*/
int scenario_m2(string arguments)
{
        smatch match;    
        bool all_data_found=true;
        int h,w,n,k;
        n=FIELD_SIZE;
        if(regex_search(arguments,match,regex("-k(\\d{1,6})")))
            k=atoi(match.str(1).c_str());
        else
            all_data_found=false;

        if(regex_search(arguments,match,regex("-n(\\d{1,6})")))
            n=atoi(match.str(1).c_str());

        if(regex_search(arguments,match,regex("-h(\\d{1,6})")))
            h=atoi(match.str(1).c_str());
        else
            all_data_found=false;

        if(regex_search(arguments,match,regex("-w(\\d{1,6})")))
            w=atoi(match.str(1).c_str());
        else
            all_data_found=false;

        if(!all_data_found)
        {
            cerr<<"NIE PODANO WSZYSTKICH DANYCH!\n";
            return -1;
        }
        // jezeli mamy wiecej pomidorkow niz pomiesci nasze pole
        // albo plachte wieksza niz nasze pole
        // albo plachta badz pole ma jakis wymiar rowny/mniejszy zero
        if( h>n || w>n || n<=0 || h<=0 || w<=0)
        {
            cerr<<"BLENDE DANE!\n";
            return -1;
        }
        Generator generator(n,k);

        Algorithm tomatoe_search(k,h,w);

        Field field = generator.generate();
        tomatoe_search.set_field(field);

        cout<<"\tPoszukiwanie zajelo: "<<tomatoe_search.run()/1000000.0<<" sekund"<<endl;
        cout<<"\tnajlepszy wynik:\n";
        cout<<"\t"<<tomatoe_search.get_count()<<" krzakow przykrytych dla punktu: ("<<tomatoe_search.get_location().first<<", "<<tomatoe_search.get_location().second<<")"<<endl;
        cout<<"\tWymiary plachty: "<<tomatoe_search.get_sizes().first<<" x "<<tomatoe_search.get_sizes().second<<endl;
        return 0;        
}
/*
    ---------------------m3---------------------
    przeprowadzamy benchmark
    
    k = poczatkowa liczba krzaczkow, zwiekszana przez step, maksymalnie r razy
    r = ile bedzie roznych instancji problemu
    step = o ile sie zwieksza liczba krzaczkow
    c = count, ile razy dla instancji problemu ma byc test
    h = wysokosc plachty
    w = szerokosc plachty
    n = rozmiar pola (najlepiej nie podawac)
*/
int scenario_m3(string arguments)
{
    smatch match;
    int step,r,c,n,k,h,w;
    bool h_w_inc=false;
    n=FIELD_SIZE;
    bool all_data_found=true;
    if(regex_search(arguments,match,regex("-k(\\d{1,6})")))
        k=atoi(match.str(1).c_str());
    else
        all_data_found=false;

    if(regex_search(arguments,match,regex("-step(\\d{1,5})")))
        step=atoi(match.str(1).c_str());
    else
        all_data_found=false;

    if(regex_search(arguments,match,regex("-r(\\d{1,2})")))
        r=atoi(match.str(1).c_str());
    else
        all_data_found=false;

    if(regex_search(arguments,match,regex("-c(\\d{1,2})")))
        c=atoi(match.str(1).c_str());
    else
        all_data_found=false;

    if(regex_search(arguments,match,regex("-h(\\d{1,6})")))
        h=atoi(match.str(1).c_str());
    else
        all_data_found=false;
    
    if(regex_search(arguments,match,regex("-w(\\d{1,6})")))
        w=atoi(match.str(1).c_str());
    else
        all_data_found=false;
    //dla n nie jest istotne zeby znalezc, powinnismy uzyc domyslnego n=60000
    if(regex_search(arguments,match,regex("-n(\\d{1,6})")))
        n=atoi(match.str(1).c_str());

    if(regex_search(arguments,match,regex("-hwi")))
        h_w_inc= true;
    
    if(!all_data_found)
    {
        cerr<<"NIE PODANO WSZYSTKICH DANYCH!\n";
        return -1;
    }
    if(h>n || w>n || n<=0 || h<=0 || w<=0)
    {
        cerr<<"BLENDE DANE!\n";
        return -1;
    }
    
    // ustawianie domyslnych wartosci jezli zostana podane bledne/nie zostana podane
    if(r<=0)
        r=1;
    if(c<=0)
        c=1;
    if(step<0)
        step=0;



    Algorithm tomatoe_search(k,h,w);
    Generator gen(n,k);

    vector<double> duration_times;
    vector<double> instance_sizes;

    duration_times.reserve(r);
    instance_sizes.reserve(r);

    for(int i=0; i<r; i++)
    {
        //ustawiamy w generatorze ile ma byc pomidorkow
        int k_update;
        int h_update=h;
        int w_update=w;

        if(k+(i*step)>MAX_TOMATOE_COUNT)
            k_update=MAX_TOMATOE_COUNT;
        else
            k_update = k+(i*step);

        if(h_w_inc)
        {
            if (h + (i * step) > MAX_HEIGHT_WIDTH)
                h_update = MAX_HEIGHT_WIDTH;
            else
                h_update = h + (i * step);

            if (w + (i * step) > MAX_HEIGHT_WIDTH)
                w_update = MAX_HEIGHT_WIDTH;
            else
                w_update = w + (i * step);
        }
    
        
        //pole teraz ma wiecej pomidorkow
        gen.set_tomatoes_count(k_update);
        tomatoe_search.set_n_tomatoes(k_update);
        if(h_w_inc)
        {
            tomatoe_search.set_sheet_height(h_update);
            tomatoe_search.set_sheet_width(w_update);
        }

        double average_time=0.0;
        for(int j=0; j<c; j++)
        {
            tomatoe_search.set_field(gen.generate());
            double duration = tomatoe_search.run()/1000.0;
            average_time +=duration;
        }
        duration_times.push_back(average_time/c);
        // normalizacja, nie chcemy dostac ogromnego wspolczynnika
        double a,b,c;
        a=k_update/100.0;
        b=h_update/100.0;
        c=w_update/100.0;

        instance_sizes.push_back(a*a*max(b,c));
        // cout<<a<<" "<<b<<" "<<c<<endl;
        // cout<<"popchnieto: "<<a*a;
        //cout<<endl;
    }

    double coefficient = duration_times.at(r/2)/instance_sizes.at(r/2);
    cout<<"WSPOLCZYNNIK C = "<<coefficient<<endl;
    cout<<"size = k*k*max(h,w)/1000000\n\n";
    cout<<"size\tt(size)[ms]\tq(size)\n";
    for(int i = 0; i<duration_times.size(); i++)
    {
        double q = (duration_times.at(i)/instance_sizes.at(i))/coefficient;
        cout<<instance_sizes.at(i)<<"\t"<<duration_times.at(i)<<"\t"<<q<<endl;
    }
    return 0;
}

int scenario_m4(string arguments)
{
    smatch match;
    bool all_data_found=true;
    int h,w,n,k;
    n=FIELD_SIZE;
    if(regex_search(arguments,match,regex("-k(\\d{1,6})")))
        k=atoi(match.str(1).c_str());
    else
        all_data_found=false;

    if(regex_search(arguments,match,regex("-n(\\d{1,6})")))
        n=atoi(match.str(1).c_str());

    if(regex_search(arguments,match,regex("-h(\\d{1,6})")))
        h=atoi(match.str(1).c_str());
    else
        all_data_found=false;

    if(regex_search(arguments,match,regex("-w(\\d{1,6})")))
        w=atoi(match.str(1).c_str());
    else
        all_data_found=false;

    if(!all_data_found)
    {
        cerr<<"NIE PODANO WSZYSTKICH DANYCH!\n";
        return -1;
    }
    // jezeli mamy wiecej pomidorkow niz pomiesci nasze pole
    // albo plachte wieksza niz nasze pole
    // albo plachta badz pole ma jakis wymiar rowny/mniejszy zero
    if( h>n || w>n || n<=0 || h<=0 || w<=0)
    {
        cerr<<"BLENDE DANE!\n";
        return -1;
    }

    Generator generator(n,k);

    Algorithm tomatoe_search(k,h,w);
    NaiveAlgorithm naive_search(k,h,w);

    Field field = generator.generate();
    tomatoe_search.set_field(field);
    naive_search.set_field(field);

    cout<<"\tNasz algorytm znalazl w: "<<tomatoe_search.run()/1000000.0<<" sekund"<<endl;
    cout<<"\tnajlepszy wynik:\n";
    cout<<"\t"<<tomatoe_search.get_count()<<" krzakow przykrytych dla punktu: ("<<tomatoe_search.get_location().first<<", "<<tomatoe_search.get_location().second<<")"<<endl;
    cout<<"\tWymiary plachty: "<<tomatoe_search.get_sizes().first<<" x "<<tomatoe_search.get_sizes().second<<endl;

    cout<<"\n\n\tNaiwny algorytm znalazl w: "<<naive_search.run()/1000000.0<<" sekund"<<endl;
    cout<<"\tnajlepszy wynik:\n";
    cout<<"\t"<<naive_search.get_count()<<" krzakow przykrytych dla punktu: ("<<naive_search.get_location().first<<", "<<naive_search.get_location().second<<")"<<endl;
    cout<<"\tWymiary plachty: "<<naive_search.get_sizes().first<<" x "<<naive_search.get_sizes().second<<endl;


    return 0;
}
