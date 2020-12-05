#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Generator
{
public:
    typedef std::vector<std::pair<uint32_t,uint32_t>> field_type;
private:
    int field_size;
    int tomatoes_count;
    field_type field;

    bool is_occupied(int x,int y)
    {
        for (auto i = field.begin(); i !=field.end(); i++)
        {
            if(i->first==x && i->second==y)
            {
                return true;
            }
        }
        return false;
    };

public:
    Generator(int size, int count): field_size(size), tomatoes_count(count) {};

    void generate()
    {
        field.clear();
        field.reserve(tomatoes_count);
        int k = tomatoes_count;
        srand(time(NULL));
        uint32_t tmp1,tmp2;
        while (k>0)
        {
            if(field_size > RAND_MAX)
            {
                tmp1 = rand() %(field_size-RAND_MAX-1);
                tmp1 += rand() %RAND_MAX-1;
                tmp2 = rand() %(field_size-RAND_MAX-1);
                tmp2 += rand() %RAND_MAX-1;
            }
            else
            {
                tmp1 = rand() %field_size;
                tmp2 = rand() %field_size;
            }
            if(!is_occupied(tmp1,tmp2))
            {
                field.push_back(std::make_pair(tmp1,tmp2));
            }
            k--;
        }
    }

    field_type get_field()
    {
        return field;
    }

    void print_cords()
    {
        for(auto i = field.begin();i!=field.end();i++)
        {
            std::cout<<i->first<<" "<<i->second<<"\n";
        }
    }
};

#endif