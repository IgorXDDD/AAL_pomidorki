#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#include "base.hpp"

class Algorithm : public BaseAlgorithm
{
private:
	std::chrono::microseconds run_instance();

public:
    Algorithm(uint32_t n_tomatoes, uint32_t sheet_height, uint32_t sheet_width) : BaseAlgorithm(n_tomatoes, sheet_height, sheet_width) { };
    void swap_h_w();
    long run();
};




#endif
