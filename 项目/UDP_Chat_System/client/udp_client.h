#pragma once

#include <stdio.h>
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


class udp_client
{
    public:
        udp_client(const std::string& _ip = "127.0.0.1",\
                   const int& _port = 8888);
        ~udp_client();
        int init();

        int recv_msg(std::string& out);
        int send_msg(const std::string& msg);
        void set_sock(const std::string& _ip, const int& _port);

    private:
        int sock;
        std::string ip;
        int port;
};
