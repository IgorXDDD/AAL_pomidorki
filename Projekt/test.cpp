#include <iostream>
#include <array>
const int size = 10;
using std::cout;
using std::endl;

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



int main(int argc, char *argv[])
{
    int k=0;
    std::array<std::array<int,size>,size> field = {};
    print_arr(field);

    




    return 0;
}

