/*
 * naive.cpp
 *
 *  Created on: Jan 7, 2021
 *      Author: bartlomiej
 */

#include "../include/naive.hpp"
#include <chrono>


std::chrono::microseconds NaiveAlgorithm::run_instance()
{
    pair<uint32_t,uint32_t> best_coords;
    uint32_t maxsum = 0;
    auto start = high_resolution_clock::now();
    for(uint32_t coord_x = field.min_coord(); coord_x < (int)field.max_coord() - (int)sheet_width+1; ++coord_x )
    {

        for(uint32_t coord_y = field.min_coord(); coord_y < (int)field.max_coord() - (int)sheet_height+1; ++coord_y )
        {
        	uint32_t sum = 0;
        	for( auto field_it = field.begin(); field_it != field.end(); ++field_it)
        	{
        		if(field_it->first >= coord_x && field_it->first <= (coord_x + sheet_width) && field_it->second >= coord_y &&
        				field_it->second <=( coord_y + sheet_height))
        		{
        			++sum;
        		}
        	}
        	if( sum > maxsum )
            {
                maxsum = sum;
                best_coords.first=coord_x;
                best_coords.second=coord_y;
            }
        }
    }
    if(maxsum > best_sum)
    {
        best_sum = maxsum;
        bestloc.first = best_coords.first;
        bestloc.second = best_coords.second;
        h_w_order.first = sheet_width;
        h_w_order.second = sheet_height;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    return duration;
}

long NaiveAlgorithm::run()
{
    best_sum = 0;
    auto duration = run_instance().count();
    if(sheet_height != sheet_width)
    {
        swap_h_w();
        duration += run_instance().count();
    }
    return duration;
}


void NaiveAlgorithm::swap_h_w()
{
    uint32_t tmp = sheet_height;
    sheet_height = sheet_width;
    sheet_width = tmp;
}

