#include "algorithm.hpp"
#include <regex>
#include <iomanip>
#include <cstdio>


using namespace std;

void switch_scenario(int scenario);
int handle_argc(int argv, char **argc);

int main(int argv, char* argc[])
{
    handle_argc(argv,argc);
    return 0;
}

int handle_argc(int argv, char **argc)
{
    string arguments;
    for(int i=1;i<argv;i++)
    {
        arguments+=argc[i];
        arguments+=" ";
    }

    smatch match;
    //          m1 = podajemy standardowe wejscie i wywalamy na stdout
    if(regex_search(arguments,match,regex("-m1")))
    {
        int h,k,n,w;
        cin>>h;
        cin>>w;
        cin>>n;
        cin>>k;
        int x,y;
        Generator::field_type field;
        for(int i=0;i<k;i++)
        {
            cin>>x;
            cin>>y;
            field.push_back(make_pair(x,y));
        }
        // moze jeszcze byc taka sytuacja ze uzytkownik wybiera wlasne h oraz w
        if(regex_search(arguments,match,regex("-h(\\d{1,6})")))
            h=atoi(match.str(1).c_str());
        if(regex_search(arguments,match,regex("-w(\\d{1,6})")))
            w=atoi(match.str(1).c_str());

        Algorithm tomatoe_search(n,k,h,w);
        tomatoe_search.set_field(field);
        cout<<"ZAJELO: "<<(double)(tomatoe_search.run()/1000000.0)<<" SEKUND"<<endl;
        cout<<"najlepsze:\n";
        cout<<tomatoe_search.get_count()<<" dla: "<<tomatoe_search.get_location().first<<", "<<tomatoe_search.get_location().second<<endl;
        cout<<"Dla wymiarow: "<<tomatoe_search.get_sizes().first<<", "<<tomatoe_search.get_sizes().second<<endl;
        
        return 0;
    }


    //          m2 = tutaj generujemy
    else if (regex_search(arguments,match,regex("-m2")))
    {
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

        //jezeli mamy wiecej pomidorkow niz pomiesci nasze pole
        // albo plachte wieksza niz nasze pole
        // albo plachta badz pole ma jakis wymiar rowny zero
        if( h>n || w>n || n<=0 || h<=0 || w<=0)
        {
            cerr<<"BLENDE DANE!\n";
            return -1;
        }

        Generator generator(n,k);
        generator.generate();
        Algorithm tomatoe_search(k,n,h,w);
        tomatoe_search.set_field(generator.get_field());
        cout<<"ZAJELO: "<<(double)(tomatoe_search.run()/1000000.0)<<" SEKUND"<<endl;
        cout<<"najlepsze:\n";
        cout<<tomatoe_search.get_count()<<" dla: "<<tomatoe_search.get_location().first<<", "<<tomatoe_search.get_location().second<<endl;
        cout<<"Dla wymiarow: "<<tomatoe_search.get_sizes().first<<", "<<tomatoe_search.get_sizes().second<<endl;
        return 0;        
    }
    //          m3 = przeprowadzamy benchmark
    // k = poczatkowa liczba krzaczkow, zwiekszana przez step, maksymalnie r razy
    // r = ile bedzie roznych instancji problemu
    // step = o ile sie zwieksza liczba krzaczkow
    // c = count, ile razy dla instancji problemu ma byc test
    // h = wysokosc plachty
    // w = szerokosc plachty
    // n = rozmiar pola (najlepiej nie podawac)
    else if (regex_search(arguments,match,regex("-m3")))
    {
        int step,r,c,n,k,h,w;
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
        
        if(!all_data_found)
        {
            cerr<<"NIE PODANO WSZYSTKICH DANYCH!\n";
            return -1;
        }
        if(h>n || w>n || n<=0 || h<=0 || w<=0)
        {
            cerr<<"BLENDE DANE!\n";
            // cout<<"h = "<<h<<endl;
            // cout<<"w = "<<w<<endl;
            // cout<<"n = "<<n<<endl;
            // cout<<"k = "<<k<<endl;
            // cout<<"step = "<<step<<endl;
            // cout<<"r = "<<r<<endl;
            // cout<<"c = "<<c<<endl;

            return -1;
        }
        if(r<=0)
            r=1;
        if(c<=0)
            c=1;
        if(step<0)
            step=0;
        Algorithm tomatoe_search(n,k,h,w);
        Generator gen(n,k);


        cout<<"\t\tAlgorytm z asymptota O(k*h*w)\n";
        cout<<"n"<<"\tk"<<"\th"<<"\tw"<<"\tczas"<<"\td(k*h*w)"<<"\td(czas)"<<"\tq"<<endl;
        //printf("\tAlgorytm z asymptota O(k*h*w)\n");
        
        
        //cout<<"n\tk\th\tw\tczas\tzloz\t\tcz_f\tzl_f\n";
        for(int i=0; i<r; i++)
        {
            if(k+(i*step)>MAX_TOMATOE_COUNT)
            {
                cerr<<"Przekroczenie maksymalnego k!\n";
                break;
            }
            //ustawiamy w generatorze ile ma byc pomidorkow
            gen.set_tomatoes_count(k+(i*step));
            //algorytmowi tez mowimy ile jest pomidorkow
            tomatoe_search.setparams(k+(i*step),h,w);
            double recent_real =1.0;
            double current_real =1.0;
            double current_theory =1.0;
            double recent_theory =(k+(i*step))*h*w;
            for(int j=0; j<c; j++)
            {
                //pobieramy wspolrzedne pomidorkow wszystkich z genertatora (generujemy)
                tomatoe_search.set_field(gen.generate());
                tomatoe_search.set_sheet( (h+100*j)>n?n:(h+100*j), (w+100*j)>n?n:(w+100*j));
                double duration = (double)(tomatoe_search.run()/1000000.0);
                
                //odpalamy alg 
                current_theory = ((k+(i*step))*tomatoe_search.get_sizes().first*tomatoe_search.get_sizes().second);
                double tmp = current_theory;
                cout<<std::setprecision(10)<<n<<"\t"<<k+(i*step)<<"\t"<<tomatoe_search.get_sizes().first<<"\t"<<tomatoe_search.get_sizes().second<<"\t"<<duration<<"\t";
                current_real = duration/recent_real;
                current_theory = current_theory/recent_theory;
                cout<<std::setprecision(10)<<current_theory<<"\t "<<current_real<<"\t"<<current_theory/current_real<<endl;
                //printf("%6d %6d %6d %6d %10.3lf %10ld %6.3lf %6.3lf %6.3lf",n,k+(i*step),tomatoe_search.get_sizes().first,tomatoe_search.get_sizes().second,duration,tmp,current_theory,current_real,current_theory/current_real);
                recent_real=duration;
                recent_theory=tmp;
            }
            cout<<endl;
        }
    }
    else
    {
        cout<<"NIE ZNALEZIONO\n";
    }
    
}
