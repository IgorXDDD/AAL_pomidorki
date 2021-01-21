#include "generator.hpp"
#include "regex"
#include <iostream>

#define FIELD_SIZE 60000

using namespace std;

int main(int argv, char **argc)
{
    std::string arguments;
    for(int i=1;i<argv;i++)
    {
        arguments+=argc[i];
        arguments+=" ";
    }
    std::smatch match;
    int k,n,h,w;
    if(regex_search(arguments,match,std::regex("-k(\\d{1,6})")))
    {
        k=atoi(match.str(1).c_str());
    }
    else
    {
        std::cerr<<"BLEDNE DANE\n";
        return -1;
    }
    //h oraz w stają sie początkowo 1/5 n, potem najwyzej beda oddzielnie podane
    if(regex_search(arguments,match,std::regex("-n(\\d{1,6})")))
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
        std::cerr<<"BLEDNE DANE\n";
        return -1;
    }

    if(regex_search(arguments,match,std::regex("-h(\\d{1,6})")))
    {
        h=atoi(match.str(1).c_str());
    }
    if(regex_search(arguments,match,std::regex("-w(\\d{1,6})")))
    {
        w=atoi(match.str(1).c_str());
    }
    if(h>10000 || w>10000)
    {
        std::cerr<<"BLEDNE DANE\n";
        return -1;
    }
    Generator gen(n,k);
    gen.generate();
    //oddzielnie h i w podajemy
    std::cout<<h<<"\t"<<w<<std::endl;
    gen.print_to_std();
    return 0;
}
