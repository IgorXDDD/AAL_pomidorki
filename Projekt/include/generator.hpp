#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "../include/field.hpp"


class Generator
{

private:
    int field_size;
    int tomatoes_count;
    Field field;

public:
    Generator(int size, int count): field_size(size), tomatoes_count(count) {};
    void set_tomatoes_count(int count){ this->tomatoes_count = count; }
    Field generate();
    Field get_field(){ return field; }
    void print_cords();
    void print_to_std();
};

#endif
