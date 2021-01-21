#include "generator.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <regex>



Field Generator::generate()
{
	field.init(tomatoes_count);
	int k = tomatoes_count;
	srand(time(NULL));
	uint32_t tomato_x,tomato_y;
	while (k>0)
	{
		if(field.max_coord() > RAND_MAX)
		{
			tomato_x = rand() %(field.max_coord()-RAND_MAX-1);
			tomato_x += rand() %RAND_MAX-1;
			tomato_y = rand() %(field.max_coord()-RAND_MAX-1);
			tomato_y += rand() %RAND_MAX-1;
		}
		else
		{
			tomato_x = rand() %field.max_coord();
			tomato_y = rand() %field.max_coord();
		}
		if(!field.is_occupied(tomato_x, tomato_y))
		{
			field.add(std::make_pair(tomato_x,tomato_y));
		}
		else
			continue;

		k--;
	}
	return field;
}


void Generator::print_cords()
{
    for(auto i = field.begin();i!=field.end();i++)
    {
        std::cout<<i->first<<" "<<i->second<<"\n";
    }
}

void Generator::print_to_std()
{
    std::cout<<field.max_coord()<<"\t"<<tomatoes_count<<std::endl;
    for(auto i = field.begin();i!=field.end();i++)
    {
        std::cout<<i->first<<"\t"<<i->second<<"\n";
    }
}


