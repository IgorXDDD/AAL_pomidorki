/*
 * algorithm.cpp
 *
 *  Created on: Jan 7, 2021
 *      Author: bartlomiej
 */
#include "../include/algorithm.hpp"

#include <map>
#include <chrono>

std::chrono::microseconds Algorithm::run_instance()
{
    map<uint32_t,vector<uint32_t>> potentially_covered;
    //wrzucamy do wektora wszystkie
    for(auto i = field.begin(); i != field.end(); ++i)
        potentially_covered[i->first].push_back(i->second);

    pair<uint32_t,uint32_t> best_coords;
    uint32_t maxsum = 0;

    auto start = high_resolution_clock::now();

    //przechodzimy po kazdym z punktow
    // zlozonosc * k
    for(auto tomato = field.begin(); tomato != field.end(); ++tomato)
    {
        vector<uint32_t> pointsdown;
        //16
        pointsdown.resize(field.max_coord());


        //przechodzimy po sasiedztwie punktu roboczego
        // zlozonosc * h
        for(uint32_t coord_x = max(tomato->first-(sheet_width-1), field.min_coord()); coord_x < min(tomato->first + sheet_width, field.max_coord()); ++coord_x)
        {
        	uint32_t tomatoes_covered = 0;
            if(potentially_covered.find(coord_x) != potentially_covered.end())
            {
            	for(uint32_t k = 0; k<potentially_covered[coord_x].size(); k++)
					{
						if((tomato->second <= potentially_covered[coord_x].at(k)) && (potentially_covered[coord_x].at(k) <= (tomato->second + sheet_width)))
						{
							++tomatoes_covered;
						}
				}
            }
            pointsdown[coord_x] = tomatoes_covered;
        }
        for(uint32_t coord_x = (1 - sheet_width); coord_x < sheet_width; ++coord_x)
        {
        	uint32_t sum = 0;
            for(uint32_t k = max(tomato->first + coord_x, field.min_coord()); k < min(tomato->first + coord_x + sheet_width + 1, field.max_coord()); ++k)
            {
                sum+=pointsdown.at(k);
            }
            if(sum > maxsum)
            {
                maxsum = sum;
                best_coords.first = tomato->first + coord_x;
                best_coords.second = tomato->second;
            }
        }

        //korekta jezeli poza granicami
        best_coords.first = min(field.max_coord() - sheet_width, best_coords.first);
        best_coords.second = min(field.max_coord() - sheet_height, best_coords.second);
    }

    //jezeli dane wykonanie dało najlepszy wynik to zapisz ten wynik
    //przyda się on później kiedy będziemy chcieli wydobyć najlepszy wynik
    if(maxsum > best_sum)
    {
        best_sum = maxsum;
        bestloc.first = best_coords.first;
        bestloc.second = best_coords.second;
        h_w_order.first = sheet_height;
        h_w_order.second = sheet_width;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    return duration;
}

long Algorithm::run()
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

void Algorithm::swap_h_w()
{
    uint32_t tmp = sheet_height;
    sheet_height = sheet_width;
    sheet_width = tmp;
}
