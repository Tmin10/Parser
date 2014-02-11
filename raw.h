#ifndef RAW_H
#define RAW_H

#include "market.h"

class raw : public market
{
public:
    raw(std::string name, std::string count, std::string price);
    std::string print();
protected:
    std::string count, price;
};

#endif // RAW_H
