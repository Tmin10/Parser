#include "production.h"

production::production()
{
    type=name;
    this->count=count;
    this->price=price;
}

std::string production::print()
{
    return type+": "+count+" units, price: "+price;
}
