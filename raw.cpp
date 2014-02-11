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
