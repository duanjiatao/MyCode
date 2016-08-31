#pragma once

#include <iostream>
#include <string>

#include "my_json.h"

class udp_data
{
public:
    udp_data();
    ~udp_data();

    void to_string(std::string& out);
    void to_value(std::string& in);

    const std::string get_nickname();
    const std::string get_school();
    const std::string get_msg();
    const std::string get_cmd();

    void set_nickname(const std::string& _n);
    void set_school(const std::string& _s);
    void set_msg(const std::string& _m);
    void set_cmd(const std::string& _c);

private:
    std::string nickname;
    std::string school;
    std::string msg;
    std::string cmd;


};
