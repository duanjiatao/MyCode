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


void my_insert(char* query_string)
{
    if(!query_string)
    {
        return;
    }

    // name=xxx&sex=xxx
    char* ptr = query_string;
    char* name = NULL;
    char* sex = NULL;

    while(*ptr != '\0')
    {
        if(*ptr == '=' && name == NULL)
        {
            name = ptr + 1;
            ++ptr;
            continue;
        }

        if(*ptr == '&')
        {
            *ptr = '\0';
        }

        if(*ptr == '=' && sex == NULL && name != NULL)
        {
            sex = ptr + 1;
            break;
        }

        ++ptr;
    }

    const std::string cols = "(NAME, SEX)";
    std::string values = "('";
    values += name;
    values += "', '";
    values += sex;
    values += "')";

    std::cout<<"cols: "<<cols.c_str()<<std::endl;
    std::cout<<"values: "<<values.c_str()<<std::endl;

    mysql_api* db = new mysql_api();
    db->my_connect();
    db->my_insert(cols, values);
    delete db;
}


int main()
{
    char method[_SIZE_/10];
    char query_string[_SIZE_];
    int content_length = -1;
    memset(method, '\0', sizeof(method));
    memset(query_string, '\0', sizeof(query_string));

    if(getenv(METHOD))
    {
        strcat(method, getenv(METHOD));
    }
    std::cout<<"method: "<<method<<std::endl;

    if(strcasecmp(method, "GET") == 0)
    {
        if(getenv(QUERY))
        {
            strcat(query_string, getenv(QUERY));
            std::cout<<"query_string: "<<query_string<<std::endl;
            my_insert(query_string);
        }
    }
    else if(strcasecmp(method, "POST") == 0)
    {
        if(getenv(CONTLEN))
        {
            content_length = atoi(getenv(CONTLEN));
            std::cout<<"content_length: "<<content_length<<std::endl;
        }
        if(content_length != -1)
        {
            char c = '\0';
            int i = 0;
            for(; i < content_length; ++i)
            {
                if(read(0, &c, 1) > 0)
                {
                    query_string[i] = c;
                }
            }
            query_string[i] = '\0';
            std::cout<<"query_string: "<<query_string<<std::endl;
            my_insert(query_string);
        }
    }
    else
    {}


    return 0;
}


