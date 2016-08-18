//my_insert_cgi.cpp

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>

#include "mysql_api.h"

#define METHOD "REQUEST_METHOD"
#define CONTLEN "CONTENT_LENGTH"
#define QUERY "QUERY_STRING"
#define _SIZE_ 1024


void mySelect()
{
    std::string header[3];
    std::string data[1024][3];
    int rows = -1;
    int cols = -1;

    std::cout<<"<html>"<<std::endl;

    mysql_api* db = new mysql_api();
    db->my_connect();
    std::cout<<"<br/>";
    db->my_select(header, data, rows, cols);

    std::cout<<"<table border=\"1\" width=\"30%\" cellspacing=\"0\">"<<std::endl;

    int i = -1;
    int j = 0;
    for(; i < rows; ++i)
    {
        std::cout<<"<tr align=\"center\">"<<std::endl;
        //std::cout<<"<tr>"<<std::endl;
        for(j = 0; j < cols; ++j)
        {
            std::cout<<"<td>";
            if(i == -1)
            {
                std::cout<<header[j]<<"\t\t";
            }
            else
            {
                std::cout<<data[i][j]<<"\t\t";
            }
            std::cout<<"</td>"<<std::endl;
        }

        std::cout<<"</tr>"<<std::endl;
    }

    std::cout<<"</table>"<<std::endl;
    std::cout<<"</html>"<<std::endl;

    delete db;
}

int main()
{
    mySelect();

    return 0;
}


