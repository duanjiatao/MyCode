#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <map>

using namespace std;

#include "comm.h"
#include "data_pool.h"
#include "udp_data.h"


class udp_server
{
    public:
        udp_server(const std::string& _ip = "127.0.0.1",\
                   const int& _port = 8888);
        ~udp_server();
        int init();

        int recv_msg(std::string& out);
        int broadcast_msg();

    private:
        bool is_friend_exist(const std::string& key);
        int add_friend(const struct sockaddr_in& cli);
        int del_friend(const struct sockaddr_in& cli);
        int send_msg(const struct sockaddr_in& client,\
                     const socklen_t& len,\
                     const std::string& msg);
    private:
        int sock;
        std::string ip;
        int port;
        std::map<std::string, struct sockaddr_in> online_user;
        data_pool pool;
};
