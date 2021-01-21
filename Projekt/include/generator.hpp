#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "../include/field.hpp"

class Generator
{

private:
    int tomatoes_count;
    Field field;

public:
    Generator(int size, int count): tomatoes_count(count) {field.set_size(size);}
    void set_tomatoes_count(int count){ this->tomatoes_count = count; }
    Field generate();
    Field get_field(){ return field; }
    void print_cords();
    void print_to_std();
    void set_field_size(uint32_t n) { field.set_size(n);}
};

#endif

