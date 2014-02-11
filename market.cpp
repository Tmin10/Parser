#include "market.h"

market::market()
{
}

std::string market::get_type()
{
    return type;
}

void market::set_type(std::string name)
{
    type=name;
}


