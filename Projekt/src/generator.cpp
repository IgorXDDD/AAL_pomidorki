#include "../include/generator.hpp"

#include <ctime>
#include <iostream>


Field Generator::generate()
{
	field.init(tomatoes_count);
	int k = tomatoes_count;
	srand(time(NULL));
	uint32_t tomato_x,tomato_y;
	while (k>0)
	{
		if(field_size > RAND_MAX)
		{
			tomato_x = rand() %(field_size-RAND_MAX-1);
			tomato_x += rand() %RAND_MAX-1;
			tomato_y = rand() %(field_size-RAND_MAX-1);
			tomato_y += rand() %RAND_MAX-1;
		}
		else
		{
			tomato_x = rand() %field_size;
			tomato_y = rand() %field_size;
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
    std::cout<<field_size<<" "<<tomatoes_count<<std::endl;
    for(auto i = field.begin();i!=field.end();i++)
    {
        std::cout<<i->first<<" "<<i->second<<"\n";
    }
}

