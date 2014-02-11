#ifndef PRODUCTION_H
#define PRODUCTION_H

class production : public market
{
public:
    production(std::string name, std::string count, std::string price);
    std::string print();
protected:
    std::string count, price;
};

#endif // PRODUCTION_H
