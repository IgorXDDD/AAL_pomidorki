/*
 * field.hpp
 *
 *
 *      Author: bartlomiej
 */

#ifndef FIELD_HPP_
#define FIELD_HPP_

#include <vector>
#include <cstdint>


class Field
{
private:
	typedef std::pair<uint32_t,uint32_t> tomato;
	std::vector<tomato> field;
	static const uint32_t MINIMAL_COORDINATE = 0;
	static const uint32_t MAXIMAL_COORDINATE = 60000;

public:

	void init(int field_size)
	{
		this->field = std::vector<tomato>();
		this->field.reserve(field_size);
	}

    bool is_occupied(uint32_t tomato_x, uint32_t tomato_y)
    {
        for (auto i = field.begin(); i !=field.end(); i++)
        {
            if(i->first==tomato_x && i->second==tomato_y)
            {
                return true;
            }
        }
        return false;
    };
    uint32_t min_coord(){ return MINIMAL_COORDINATE; }
    uint32_t max_coord(){ return MAXIMAL_COORDINATE; }
    void add(tomato tomato){ field.push_back(tomato); }
    std::vector<tomato>::const_iterator begin() const { return field.begin(); }
	std::vector<tomato>::iterator begin(){ return field.begin(); }
	std::vector<tomato>::const_iterator end() const { return field.end(); }
	std::vector<tomato>::iterator end(){ return field.end(); }
};



#endif /* FIELD_HPP_ */
