#ifndef PARSER_H
#define PARSER_H

#include <iostream>

#include "raw.h"
#include "production.h"

class parser
{
public:
    parser(std::string login, std::string password);
    bool auth ();

    raw get_food_raw();
    raw get_weapon_raw();

    production get_weapon();
    production get_food();

    std::string get_token();
    std::string get_cookies();



private:
    std::string login, password, token, cookies, s;
};

#endif // PARSER_H
