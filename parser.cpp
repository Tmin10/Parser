#include "parser.h"
#include "http.h"

const char DOMAIN[]={"www.erepublik.com"};

const std::string MAIN_PAGE="en";
const std::string LOGIN_PAGE="en/login";

const std::string FOOD_RAW_MARKET_PAGE="en/economy/market/41/7/1/citizen/0/price_asc/1";
const std::string WEAPON_RAW_MARKET_PAGE="en/economy/market/41/12/1/citizen/0/price_asc/1";
const std::string WEAPON_MARKET_PAGE="en/economy/market/41/2/7/citizen/0/price_asc/1";
const std::string FOOD_MARKET_PAGE="en/economy/market/41/1/7/citizen/0/price_asc/1";

std::string get="GET";
std::string post="POST";

using namespace std;

parser::parser(std::string login, std::string password)
{
    this->login=login;
    this->password=password;
}

std::string parser::get_token()
{
    return token;
}

std::string parser::get_cookies()
{
    return cookies;
}

bool parser::auth()
{
    s="\r\n"
                     "User-Agent: Mozilla/5.0\r\n"
                     "Accept: text/html\r\n"
                     "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4\r\n"
                     "Accept-Charset: windows-1251,utf-8;q=0.7,*;q=0.3\r\n"
                     "Connection: keep-alive\r\n";
    http *parser = new http();

    //Get auth token
    string html = parser->get_page(get ,DOMAIN, MAIN_PAGE, s+"\r\n", 23, 25);
    if (html.length()==0)\
    {
        cout<<"Any http error, void answer for request given"<<std::endl;
        delete parser;
        return false;
    }

    cout<<html<<endl;
    string token = html.substr(html.find("name=\"_token\"")+21,32);
    cout<<"Site token: "<<token<<endl;
    this->token=token;

    //Login


    html=parser->get_page(post, DOMAIN, LOGIN_PAGE, s+"Content-Length:101\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n_token="+this->token+"&citizen_email="+this->login+"&citizen_password="+this->password, 0, 1);
    if (html.length()==0)\
    {
        cout<<"Any http error, void answer for request given"<<std::endl;
        delete parser;
        return false;
    }
    string cookies="erpk_auth=1;"+html.substr(html.find("erpk_mid="), 42);
    cookies+=html.substr(html.find("erpk="), 33);
    this->cookies=cookies;
    cout<<endl<<"Auth cookie: "<<cookies<<endl;


    delete parser;
    return true;

}

raw parser::get_food_raw()
{
    //Get markets pages
    http *parser = new http();

    string html=parser->get_page(get, DOMAIN, FOOD_RAW_MARKET_PAGE, s+"Cookie: "+cookies+" \r\n\r\n", 153, 161);
    cout<<endl<<html<<endl;

    string temp_count = html.substr(html.find("m_stock"), 70);
    string count = "";
    cout<<endl<<temp_count<<endl;

    for (int i=0; i<temp_count.length(); i++)
    {
        if ((int)temp_count[i]>47&&(int)temp_count[i]<58)
            count+=temp_count[i];
    }
    string temp_price = html.substr(html.find("stprice")+20, 40);
    //cout<<endl<<temp_price<<endl;
    string price = "";
    for (int i=0; i<temp_price.length(); i++)
    {
        if (((int)temp_price[i]>47&&(int)temp_price[i]<58)||(int)temp_price[i]==(int)'.')
            price+=temp_price[i];
    }

    cout<<count<<" "<<price<<endl;

    delete parser;

    raw *out = new raw("Grain", count, price);
    return *out;
}


raw parser::get_weapon_raw()
{
    //Get markets pages
    http *parser = new http();

    string html=parser->get_page(get, DOMAIN, WEAPON_RAW_MARKET_PAGE, s+"Cookie: "+cookies+" \r\n\r\n", 153, 161);
    cout<<endl<<html<<endl;

    string temp_count = html.substr(html.find("m_stock"), 70);
    string count = "";
    cout<<endl<<temp_count<<endl;

    for (int i=0; i<temp_count.length(); i++)
    {
        if ((int)temp_count[i]>47&&(int)temp_count[i]<58)
            count+=temp_count[i];
    }
    string temp_price = html.substr(html.find("stprice")+20, 40);
    //cout<<endl<<temp_price<<endl;
    string price = "";
    for (int i=0; i<temp_price.length(); i++)
    {
        if (((int)temp_price[i]>47&&(int)temp_price[i]<58)||(int)temp_price[i]==(int)'.')
            price+=temp_price[i];
    }

    cout<<count<<" "<<price<<endl;

    delete parser;

    raw *out = new raw("Iron", count, price);
    return *out;
}

production parser::get_weapon()
{
    //Get markets pages
    http *parser = new http();

    string html=parser->get_page(get, DOMAIN, WEAPON_MARKET_PAGE, s+"Cookie: "+cookies+" \r\n\r\n", 153, 161);
    cout<<endl<<html<<endl;

    string temp_count = html.substr(html.find("m_stock"), 70);
    string count = "";
    cout<<endl<<temp_count<<endl;

    for (int i=0; i<temp_count.length(); i++)
    {
        if ((int)temp_count[i]>47&&(int)temp_count[i]<58)
            count+=temp_count[i];
    }
    string temp_price = html.substr(html.find("stprice")+20, 40);
    //cout<<endl<<temp_price<<endl;
    string price = "";
    for (int i=0; i<temp_price.length(); i++)
    {
        if (((int)temp_price[i]>47&&(int)temp_price[i]<58)||(int)temp_price[i]==(int)'.')
            price+=temp_price[i];
    }

    cout<<count<<" "<<price<<endl;

    delete parser;

    production *out = new production("Weapon", count, price);
    return *out;
}

production parser::get_food()
{
    //Get markets pages
    http *parser = new http();

    string html=parser->get_page(get, DOMAIN, FOOD_MARKET_PAGE, s+"Cookie: "+cookies+" \r\n\r\n", 153, 161);
    cout<<endl<<html<<endl;

    string temp_count = html.substr(html.find("m_stock"), 70);
    string count = "";
    cout<<endl<<temp_count<<endl;

    for (int i=0; i<temp_count.length(); i++)
    {
        if ((int)temp_count[i]>47&&(int)temp_count[i]<58)
            count+=temp_count[i];
    }
    string temp_price = html.substr(html.find("stprice")+20, 40);
    //cout<<endl<<temp_price<<endl;
    string price = "";
    for (int i=0; i<temp_price.length(); i++)
    {
        if (((int)temp_price[i]>47&&(int)temp_price[i]<58)||(int)temp_price[i]==(int)'.')
            price+=temp_price[i];
    }

    cout<<count<<" "<<price<<endl;

    delete parser;

    production *out = new production("Food", count, price);
    return *out;
}

bool parser::send_data(raw grain, raw iron, production food, production weapon)
{
    http *parser = new http();
    string query = "c[]="+grain.get_count()+"&p[]="+grain.get_price();
    query += "&c[]="+iron.get_count()+"&p[]="+iron.get_price();
    query += "&c[]="+food.get_count()+"&p[]="+food.get_price();
    query += "&c[]="+weapon.get_count()+"&p[]="+weapon.get_price();
    string html=parser->get_page(post, "www.tmin10.ru", "parser_form", s+"Content-Type: application/x-www-form-urlencoded\r\n\r\n"+query, 0, 1);
    delete parser;
    if (html.length()==0)
    {
        cout<<"Any http error, void answer for request given"<<std::endl;
        return false;
    }
    else
        return true;
}

