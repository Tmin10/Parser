#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <sstream>
#include "http.h"

const char DOMAIN[]={"www.erepublik.com"};

const std::string LOGIN="lanagul@rainmail.biz";
const std::string PASSWORD="lanagul";

const std::string MAIN_PAGE="en";
const std::string LOGIN_PAGE="en/login";

const std::string FOOD_RAW_MARKET_PAGE="en/economy/market/41/7/1/citizen/0/price_asc/1";
const std::string WEAPON_RAW_MARKET_PAGE="en/economy/market/41/12/1/citizen/0/price_asc/1";
const std::string WEAPON_MARKET_PAGE="en/economy/market/41/2/$q$/citizen/0/price_asc/1";
const std::string FOOD_MARKET_PAGE="en/economy/market/41/1/$q$/citizen/0/price_asc/1";


using namespace std;

int main(int argc, char* argv[])
{
    string get="GET";
    string post="POST";

    string s="\r\n"
                     "User-Agent: Mozilla/5.0\r\n"
                     "Accept: text/html\r\n"
                     "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4\r\n"
                     "Accept-Charset: windows-1251,utf-8;q=0.7,*;q=0.3\r\n"
                     "Connection: keep-alive\r\n";
    http *parser = new http();

    //Get auth token
    string html = parser->get_page(get ,DOMAIN, MAIN_PAGE, s+"\r\n", 22, 24);
    if (html.length()==0)\
    {
        cout<<"Any http error, void answer for request given"<<std::endl;
        return EXIT_FAILURE;
    }
    string token = html.substr(html.find("name=\"_token\"")+21,32);
    cout<<"Site token: "<<token<<endl;

    //Login
    html=parser->get_page(post, DOMAIN, LOGIN_PAGE, s+"Content-Length:101\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n_token="+token+"&citizen_email=lanagul%40rainmail.biz&citizen_password=lanagul", 0, 1);
    string cookies="erpk_auth=1;"+html.substr(html.find("erpk_mid="), 42);
    cookies+=html.substr(html.find("erpk="), 33);
    cout<<endl<<"Auth cookie: "<<cookies<<endl;

    //Get markets pages
    html=parser->get_page(get, DOMAIN, FOOD_RAW_MARKET_PAGE, s+"Cookie: "+cookies+" \r\n\r\n", 151, 171);
    cout<<endl<<html<<endl;



    return (EXIT_SUCCESS);
}
