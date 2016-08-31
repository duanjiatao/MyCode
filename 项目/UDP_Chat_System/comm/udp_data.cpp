#include "udp_data.h"

udp_data::udp_data()
{}

udp_data::~udp_data()
{}

void udp_data::to_string(std::string& out)
{
    Json::Value _val;

    _val["nickname"] = nickname;
    _val["school"] = school;
    _val["msg"] = msg;
    _val["cmd"] = cmd;

    my_json::serialize(_val, out);
}

void udp_data::to_value(std::string& in)
{
    Json::Value _val;
    my_json::unserialize(in, _val);

    nickname = _val["nickname"].asString();
    school = _val["school"].asString();
    msg = _val["msg"].asString();
    cmd = _val["cmd"].asString();
}

const std::string udp_data::get_nickname()
{
    return nickname;
}

const std::string udp_data::get_school()
{
    return school;
}

const std::string udp_data::get_msg()
{
    return msg;
}

const std::string udp_data::get_cmd()
{
    return cmd;
}

void udp_data::set_nickname(const std::string& _n)
{
    nickname = _n;
}

void udp_data::set_school(const std::string& _s)
{
    school = _s;
}

void udp_data::set_msg(const std::string& _m)
{
    msg = _m;
}

void udp_data::set_cmd(const std::string& _c)
{
    cmd = _c;
}

#ifdef _UDP_DATA_MAIN_
int main()
{
    udp_data data("djt", "sust", "hello world", "None");
    std::string _s;
    data.to_string(_s);
    std::cout<<_s<<std::endl;

    return 0;
}
#endif





