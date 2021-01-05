#include "algorithm.hpp"
#include <regex>


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
            cout<<"h = "<<h<<endl;
            cout<<"w = "<<w<<endl;
            cout<<"n = "<<n<<endl;
            cout<<"k = "<<k<<endl;
            cout<<"step = "<<step<<endl;
            cout<<"r = "<<r<<endl;
            cout<<"c = "<<c<<endl;

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
            cout<<"\t\tTestowanie dla k = "<<k+(i*step)<<", h = "<<h<<", w = "<<w<<endl;
            for(int j=0; j<r; j++)
            {
                //pobieramy wspolrzedne pomidorkow wszystkich z genertatora (generujemy)
                tomatoe_search.set_field(gen.generate());
                tomatoe_search.set_sheet(h+100*j,w+100*j);
                //odpalamy alg 
                cout<<j<<"-ta iteracja. h = "<<h+100*j<<", w = "<<w+100*j<<" - ZAJELO: "<<(double)(tomatoe_search.run()/1000000.0)<<" SEKUND"<<endl;
                cout<<"\tNajlepsze:\n";
                cout<<"\t"<<tomatoe_search.get_count()<<" dla: "<<tomatoe_search.get_location().first<<", "<<tomatoe_search.get_location().second<<endl;
                cout<<"\tDla wymiarow: "<<tomatoe_search.get_sizes().first<<", "<<tomatoe_search.get_sizes().second<<endl;
            }
        }
    }
    else
    {
        cout<<"NIE ZNALEZIONO\n";
    }
    
}
