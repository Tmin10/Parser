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

http::http()
{

}

std::string http::get_page(std::string method, const char *url, std::string page, std::string request, int from, int to)
{
    char message[999];
    char buf[500];
    std::stringstream conv;
    std::string out ="";
    std::string start = method+" /"+page+" HTTP/1.1\r\nHost: ";
    conv<<start<<url<<request;
    std::cout<<std::endl<<conv.str()<<std::endl;
    conv.read(message,999);
    //std::cout<<message<<std::endl<<std::endl;
    int sock;
    struct sockaddr_in addr;
    struct hostent* raw_host;
    raw_host = gethostbyname(url);
    if (raw_host == NULL)
    {
        std::cout<<"ERROR, no such host";
        exit(0);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    bcopy((char *)raw_host->h_addr,(char *)&addr.sin_addr, raw_host->h_length);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
       std::cerr<<"connect error"<<std::endl;
        exit(2);
    }
    send(sock, message, sizeof(message), 0);

    for (int i=0; i<to; i++)
    {
        buf[0]=NULL;
        recv(sock, buf, sizeof(buf), 0);

        if (i>=from)
        {
           out+=buf;
        }
    }

    return out;
}
