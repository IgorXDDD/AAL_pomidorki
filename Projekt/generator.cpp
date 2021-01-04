#include "generator.hpp"
#include <regex>
#include <string>

using namespace std;

int main(int argv, char **argc)
{
    string arguments;
    for(int i=1;i<argv;i++)
    {
        arguments+=argc[i];
        arguments+=" ";
    }
    smatch match;
    int k,n,h,w;
    if(regex_search(arguments,match,regex("-k(\\d{1,6})")))
    {
        k=atoi(match.str(1).c_str());
    }
    else
    {
        cerr<<"BLEDNE DANE\n";
        return -1;
    }
    //h oraz w stają sie początkowo 1/5 n, potem najwyzej beda oddzielnie podane
    if(regex_search(arguments,match,regex("-n(\\d{1,6})")))
    {
        n=atoi(match.str(1).c_str());
        h=(n/5)>1?(n/5):1;
        w=(n/5)>1?(n/5):1;
    }
    else
    {
        n=FIELD_SIZE;
        h=10000;
        w=10000;
    }
    if(n<0 || k<0)
    {
        cerr<<"BLEDNE DANE\n";
        return -1;
    }

    if(regex_search(arguments,match,regex("-h(\\d{1,6})")))
    {
        //cout<<match.str(1)<<endl;
        h=atoi(match.str(1).c_str());
    }
    if(regex_search(arguments,match,regex("-w(\\d{1,6})")))
    {
        //cout<<match.str(1)<<endl;
        w=atoi(match.str(1).c_str());
    }
    if(h>10000 || w>10000)
    {
        cerr<<"BLEDNE DANE\n";
        return -1;
    }
    Generator gen(n,k);
    gen.generate();
    //oddzielnie h i w podajemy
    cout<<h<<" "<<w<<endl;
    gen.print_to_std();
    return 0;
}
