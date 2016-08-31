#include "udp_client.h"


udp_client::udp_client(const std::string& _ip, const int& _port)
    :ip(_ip)
    ,port(_port)
{
    this->sock = -1;
    this->init();
}

udp_client:: ~udp_client()
{
    if(-1 != this->sock)
    {
        close(sock);
    }
}

int udp_client::init()
{
    this->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        print_log("socket error", __FUNCTION__, __LINE__);
        return 1;
    }

    return 0;
}

void udp_client::set_sock(const std::string& _ip, const int& _port)
{
    ip = _ip;
    port = _port;
}

int udp_client::recv_msg(std::string& out)
{
    char buf[SIZE];
    memset(buf, '\0', sizeof(buf));
    struct sockaddr_in peer;
    socklen_t len = sizeof(peer);
    int recv_bytes = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&peer, &len);
    if(recv_bytes < 0)
    {
        print_log("recvfrom error", __FUNCTION__, __LINE__);
        return -1;
    }
    else
    {
        buf[recv_bytes] = '\0';
        out = buf;
    }

    return recv_bytes;
}


int udp_client::send_msg(const std::string& msg)
{
    struct sockaddr_in remote;
    remote.sin_family = AF_INET;
    remote.sin_addr.s_addr = inet_addr(ip.c_str());
    remote.sin_port = htons(port);
    socklen_t len = sizeof(remote);

    int send_size = sendto(this->sock, msg.c_str(), msg.size(), 0,\
            (const struct sockaddr*)&remote, len);
    if(send_size < 0)
    {
        print_log("send msg error", __FUNCTION__, __LINE__);
        return -1;
    }

    //print_debug("send msg success");
    return send_size;
}


#ifdef _SERVER_MAIN_
int main()
{
    return 0;
}
#endif






