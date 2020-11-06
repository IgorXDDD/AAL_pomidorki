#include <iostream>
#include <array>
#include <time.h>
#include <cstdlib>
const int size = 30;
using std::cout;
using std::endl;
typedef std::array<std::array<int,size>,size> field_type;

template <std::size_t SIZE,std::size_t SIZE2>
void print_arr ( const std::array<std::array<int,SIZE>,SIZE2> & arr) 
{
    for(int i=0;i<size;++i)
    {
        for(int j=0;j<size;++j)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}

field_type generate_field(int tomatoes_count)
{
    if(tomatoes_count>(size*size))
    {
        throw std::length_error("za duzo pomidorkow :(((");
    }
    srand(time(NULL));
    field_type field = {};
    int tmp;
    while (tomatoes_count>0)
    {
        tmp = rand() % (size*size);
        if(field[0][tmp])
        {
            continue;
        }
        else
        {
            field[0][tmp]=1;
            tomatoes_count--;
        }
    }
    return field;
}


int main(int argc, char *argv[])
{
    field_type field;
    try
    {
        field= generate_field(300000);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        field = generate_field(size);
    }
    
    
    print_arr(field);
    // int count=0;
    // for(auto i = field.begin();i!=field.end();i++)
    // {
        
    // }
    
    




    return 0;
}

