/*
 * naive.hpp
 *
 *  Created on: Jan 7, 2021
 *      Author: bartlomiej
 */

#ifndef NAIVE_HPP_
#define NAIVE_HPP_

#include "../include/base.hpp"

class NaiveAlgorithm : public BaseAlgorithm
{
private:
	std::chrono::microseconds run_instance();
	bool is_covered(uint32_t tomato_x, uint32_t tomato_y);

public:
    NaiveAlgorithm(uint32_t n_tomatoes, uint32_t sheet_height, uint32_t sheet_width) : BaseAlgorithm(n_tomatoes, sheet_height, sheet_width) { };
    long run();
};




#endif /* NAIVE_HPP_ */
