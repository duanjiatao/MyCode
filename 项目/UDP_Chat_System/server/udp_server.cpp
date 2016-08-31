#include "udp_server.h"


udp_server::udp_server(const std::string& _ip, const int& _port)
    :ip(_ip)
    ,port(_port)
{
    this->sock = -1;
    this->init();
}

udp_server:: ~udp_server()
{
    if(-1 != this->sock)
    {
        close(sock);
    }
}

int udp_server::init()
{
    this->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        print_log("socket error", __FUNCTION__, __LINE__);
        return 1;
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = inet_addr((this->ip).c_str());
    local.sin_port = htons(this->port);

    if(bind(this->sock, (const struct sockaddr*)&local, sizeof(local)) < 0)
    {
        print_log("bind error", __FUNCTION__, __LINE__);
        return 2;
    }

    print_debug("init success");
    return 0;
}

int udp_server::recv_msg(std::string& out)
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
        std::cout<<"get a new msg"<<std::endl<<out<<std::endl;

        udp_data tmp;
        tmp.to_value(out);
        if(strcasecmp((tmp.get_cmd()).c_str(), "quit") == 0)
        {
            std::cout<<tmp.get_nickname()<<" quit"<<std::endl;
            pool.put_msg(out);
            del_friend(peer);
        }
        else
        {
            pool.put_msg(out);
            add_friend(peer);
        }
    }

    return recv_bytes;
}

bool udp_server::is_friend_exist(const std::string& key)
{
    std::map<std::string, struct sockaddr_in>::iterator it = online_user.find(key);
    if(it != online_user.end())
    {
        return true;
    }
    return false;
}

int udp_server::add_friend(const struct sockaddr_in& cli)
{
    std::string new_cli_ip = inet_ntoa(cli.sin_addr);
    if(!is_friend_exist(new_cli_ip))
    {
        online_user.insert(std::pair<std::string, struct sockaddr_in>(new_cli_ip, cli));
        print_debug("new friend add success");
        return 0;
    }

    print_debug("new friend add faild");
    return -1;
}

int udp_server::del_friend(const struct sockaddr_in& cli)
{
    std::string del_cli_ip = inet_ntoa(cli.sin_addr);
    if(is_friend_exist(del_cli_ip))
    {
        online_user.erase(del_cli_ip);
        print_debug("delete friend success");
        return 0;
    }

    print_debug("delete friend faild");
    return -1;
}

int udp_server::send_msg(const struct sockaddr_in& client, const socklen_t& len, const std::string& msg)
{
    int size = sendto(this->sock, msg.c_str(), msg.size(), 0, (const struct sockaddr*)&client, len);
    if(size < 0)
    {
        print_log("send msg error", __FUNCTION__, __LINE__);
        return -1;
    }

    print_debug("send msg success");
    return size;
}

int udp_server::broadcast_msg()
{
    std::string msg;
    pool.get_msg(msg);
    std::map<std::string, struct sockaddr_in>::iterator iter =  online_user.begin();
    socklen_t len = 0;
    while(iter != online_user.end())
    {
        len = sizeof(iter->second);
        send_msg(iter->second, len, msg);
        ++iter;
    }
    std::cout<<"broadcast a msg"<<std::endl<<msg<<std::endl;

    return 0;
}

#ifdef _SERVER_MAIN_
int main()
{
    return 0;
}
#endif






