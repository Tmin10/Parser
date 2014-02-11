#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "market.h"

class production : public market
{
public:
    production(std::string name, std::string count, std::string price);
    std::string print();
    std::string get_count();
    std::string get_price();

protected:
    std::string count, price;
};

#endif // PRODUCTION_H
