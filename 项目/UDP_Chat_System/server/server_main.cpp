#include <stdlib.h>
#include "udp_server.h"

void usage(const std::string arg)
{
    std::cout<<"Usage "<<arg<<"[IP] [PORT]"<<std::endl;
}


void* run_receive(void* arg)
{
    udp_server* server = (udp_server* )arg;

    std::string msg;
    while(1)
    {
        server->recv_msg(msg);
    }
}

void* run_broadcast(void* arg)
{
    udp_server* server = (udp_server* )arg;

    while(1)
    {
        server->broadcast_msg();
    }
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    udp_server* server = new udp_server(argv[1], atoi(argv[2]));

    pthread_t td_receive;
    pthread_t td_broadcast;

    pthread_create(&td_receive, NULL, run_receive, (void* )server);
    pthread_create(&td_broadcast, NULL, run_broadcast, (void* )server);

    pthread_join(td_receive, NULL);
    pthread_join(td_broadcast, NULL);

    delete server;
    return 0;
}
