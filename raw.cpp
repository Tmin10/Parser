#include "raw.h"

raw::raw(std::string name, std::string count, std::string price)
{
    type=name;
    this->count=count;
    this->price=price;
}

std::string raw::print()
{
    return type+": "+count+" units, price: "+price;
}

std::string raw::get_count()
{
    return count;
}

std::string raw::get_price()
{
    return price;
}

