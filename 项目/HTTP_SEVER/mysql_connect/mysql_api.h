//mysql_api.h

#pragma once

#include <iostream>
#include <string>
#include "mysql.h"

using namespace std;


class mysql_api
{
    public:
        mysql_api(const std::string& _host = "localhost",\
          const std::string& _user = "root",\
          const std::string& _passwd = "qq012345",\
          const std::string& _db = "http",\
          size_t _port = 3306);

        ~mysql_api();

        int my_connect();
        int my_insert(const std::string& cols, const std::string& values);
        int my_delete(const std::string& which, const std::string& value);
        int my_update(const std::string& which1, const std::string& value1,\
                      const std::string& which2, const std::string& value2);
        int my_select(std::string header[], std::string data[][3],\
                      int& row_num, int& col_num);


    private:
        MYSQL* conn;
        MYSQL_RES* res;
        string host;
        string user;
        string passwd;
        string db;
        size_t port;
};



