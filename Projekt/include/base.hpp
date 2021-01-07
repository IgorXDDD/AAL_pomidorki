/*
 * base.hpp
 *
 *  Created on: Jan 7, 2021
 *      Author: bartlomiej
 */

#ifndef BASE_HPP_
#define BASE_HPP_

#include <chrono>
#include "field.hpp"

using namespace std;
using namespace std::chrono;

class BaseAlgorithm
{
protected:
	uint32_t n_tomatoes, sheet_height, sheet_width, best_sum;
    pair<uint32_t,uint32_t> bestloc;
    pair<uint32_t,uint32_t> h_w_order;
    Field field;
public:
    BaseAlgorithm(uint32_t n_tomatoes, uint32_t sheet_height, uint32_t sheet_width) : n_tomatoes(n_tomatoes),
    		sheet_height(sheet_height), sheet_width(sheet_width){ best_sum = 0; }
    void set_n_tomatoes(uint32_t n_tomatoes){ this->n_tomatoes = n_tomatoes; }
    void set_sheet_height(uint32_t sheet_height){ this->sheet_height = sheet_height; }
    void set_sheet_width(uint32_t sheet_width){ this->sheet_width = sheet_width; }
    void set_field(Field field){ this->field = field; }
    pair<uint32_t,uint32_t> get_location(){  return bestloc; }
    pair<uint32_t,uint32_t> get_sizes(){ return h_w_order; }
    uint32_t get_count(){ return best_sum; }
};



#endif /* BASE_HPP_ */
