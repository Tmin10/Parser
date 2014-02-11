#ifndef MARKET_H
#define MARKET_H

#include <iostream>

class market
{
public:
    market();
    std::string get_type();
    void set_type(std::string);
    virtual std::string print() = 0;
protected:
    std::string type;
};

#endif // MARKET_H
