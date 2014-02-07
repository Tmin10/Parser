#ifndef HTTP_H
#define HTTP_H

class http
{
public:
    http();
    std::string static get_page(std::string method, const char *url, std::string page, std::string request, int from, int to);
};

#endif // HTTP_H
