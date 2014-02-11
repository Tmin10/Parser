#include "production.h"

production::production(std::string name, std::string count, std::string price)
{
    type=name;
    this->count=count;
    this->price=price;
}

std::string production::print()
{
    return type+": "+count+" units, price: "+price;
}

std::string production::get_count()
{
    return count;
}

std::string production::get_price()
{
    return price;
}
