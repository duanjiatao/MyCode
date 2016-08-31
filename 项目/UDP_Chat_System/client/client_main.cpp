#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <algorithm>
#include <signal.h>
#include <string>
#include <string.h>
//#include <strstream>

#include "udp_client.h"
#include "udp_data.h"
#include "cwindow.h"
using namespace std;

void usage(const std::string arg)
{
    std::cout<<"Usage "<<arg<<"[IP] [PORT]"<<std::endl;
}

std::vector<std::string> friend_list; //friend list
static std::string cur_user_nickname;
static std::string cur_user_school;

struct some_info
{
    cwindow* win_cli;
    udp_client* cli;
};

void* run_head(void* arg)
{
    some_info* info = (some_info*)arg;
    cwindow* win = info->win_cli;

    win->create_output();
    const std::string show = "Welcome to udp chat system!!!";
    win->create_head();
    WINDOW* head = win->get_win_head();
    
    int max_x, max_y;
    int x = 0;
    int y = 0;
    while(1)
    {
        getmaxyx(head, max_y, max_x);
        y = max_y/2;
        win->clr_win_line(head, y, 2);
        win->put_str_to_win(head, y, (++x)%max_x, show);
        usleep(100000);
        win->refresh_win(head);
    }
}

void* run_output(void* arg)
{
    some_info* info = (some_info*)arg;
    cwindow* win = info->win_cli;
    udp_client* cli = info->cli;

    win->create_output();
    WINDOW* output = win->get_win_output();

    int _y = 0;
    int _x = 3;
    udp_data recv_data;
    std::string recv_str;
    int max_y, max_x;
    getmaxyx(output, max_y, max_x);

    while(1)
    {
        _y = (++_y)%max_y;
        if(0 == _y)
        {
            win->clr_win_line(output, 1, max_y-1);
            continue;
        }

        win->refresh_win(output);

        recv_str = "";
        ssize_t recv_bytes = cli->recv_msg(recv_str);
        if(recv_bytes > 0)
        {
            recv_data.to_value(recv_str);
            const std::string _nickname = recv_data.get_nickname();
            const std::string _school = recv_data.get_school();
            const std::string _msg = recv_data.get_msg();
            const std::string _cmd = recv_data.get_cmd();

            std::string _output = "[";
            _output += _school;
            _output += "/";
            _output += _nickname;
            _output += "]";

            friend_list.push_back(_output); //push user into friend list
            std::vector<std::string>::iterator iter = std::unique(friend_list.begin(), friend_list.end());
            friend_list.erase(iter, friend_list.end());
            if(strcasecmp("quit", _cmd.c_str()) == 0)
            {
                std::vector<std::string>::iterator it_del = find(friend_list.begin(), friend_list.end(), _output);
                if(it_del != friend_list.end())
                {
                    friend_list.erase(it_del); //detete this user from friend list
                }
            }

            _output += ">> ";
            _output += _msg;

            if(strcasecmp("quit", _cmd.c_str()) != 0)
            {
                win->put_str_to_win(output, _y, _x, _output);
            }
        }

        win->refresh_win(output);
        usleep(10000);
    }
}

void* run_flist(void* arg)
{	
    some_info* info = (some_info*)arg;
    cwindow* win = info->win_cli;
    udp_client* cli = info->cli;

    win->create_flist();
    WINDOW* flist = win->get_win_flist();

    while(1)
    {
        int max_y, max_x;
        getmaxyx(flist, max_y, max_x);

        std::vector<std::string>::iterator iter = std::unique(friend_list.begin(), friend_list.end());
        friend_list.erase(iter, friend_list.end());

        int listSize = friend_list.size();
        int page = max_y - 3;
        int page_num = listSize/page;
        int page_mod = listSize%page;
        if(page_mod > 0)
        {
            ++page_num;
        }

        char pnum[16];
        memset(pnum, '\0', sizeof(pnum));
        sprintf(pnum, "%d", page_num);
        std::string str_page_num = pnum;

        win->refresh_win(flist);
        std::string outPage;
        int q = 0;
        for(int i = 1; i <= page_num; ++i)
        {
            char pi[16];
            memset(pi, '\0', sizeof(pi));
            sprintf(pi, "%d", i);
            std::string str_i = pi;

            outPage = str_i;
            outPage += "/";
            outPage +=  str_page_num;

            win->clr_win_line(flist, max_y-2, 1);
            win->put_str_to_win(flist, max_y-2, max_x/2-2, outPage);

            int y = 0;
            for(int j = 0; j < page; ++j)
            {
                y = (++y)%(page);
                int index = (i-1)*page + j;
                if(index < listSize)
                {
                    if(y == 0)
                    {
                        win->refresh_win(flist);
                        sleep(3);
                        win->clr_win_line(flist, 1, max_y-4);
                        continue;
                    }
                    std::string fri = friend_list[index];
                    win->put_str_to_win(flist, y, 2, fri);
                }
                else
                {
                    break;
                }
            }
        }

        win->refresh_win(flist);
        sleep(5);
    }
}

static udp_data in_data;

void* run_input(void* arg)
{
    some_info* info = (some_info*)arg;
    cwindow* win = info->win_cli;
    udp_client* cli = info->cli;

    const std::string tip = "Please enter# ";
    win->create_input();
    WINDOW* input = win->get_win_input();
    
    int _y = 1;
    int _x = 3;
    std::string get_msg;
    while(1)
    {
        get_msg = "";
        win->put_str_to_win(input, _y, _x, tip);
        win->refresh_win(input);
        win->get_str_from_win(input, get_msg);

        if(strcasecmp("quit", get_msg.c_str()) == 0)
        {
            in_data.set_msg("None");
            in_data.set_cmd("quit");
            std::string json_msg;
            in_data.to_string(json_msg);
            cli->send_msg(json_msg);
            exit(1);
        }

        //send/////////////////////////
        in_data.set_msg(get_msg);
        std::string json_msg;
        in_data.to_string(json_msg);
        cli->send_msg(json_msg);
        ///////////////////////////////

        int max_y, max_x;
        getmaxyx(input, max_y, max_x);
        win->clr_win_line(input, 1, max_y-1);
        
        usleep(100000);
    }

}

static udp_client* cli_temp;
void quit(int sig)
{
    udp_data quit_data;
    quit_data.set_nickname(cur_user_nickname);
    quit_data.set_school(cur_user_school);
    quit_data.set_msg("None");
    quit_data.set_cmd("quit");

    std::string json_msg;
    quit_data.to_string(json_msg);
    cli_temp->send_msg(json_msg);

    endwin();
    exit(2);
}


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }

    signal(SIGINT, quit);

    std::string _nickname;
    std::string _school;
    std::cout<<"Please enter your nickname# ";
    fflush(stdout);
    std::cin>>_nickname;
    std::cout<<"Please enter your school# ";
    fflush(stdout);
    std::cin>>_school;

    cwindow win;
    udp_client cli;
    win.init();
    cli.init();
    cli.set_sock(argv[1], atoi(argv[2]));

    cli_temp = &cli;
    some_info info;
    info.win_cli = &win;
    info.cli = &cli;

    cur_user_nickname = _nickname;
    cur_user_school = _school;
    in_data.set_nickname(_nickname);
    in_data.set_school(_school);

    pthread_t id_head;
    pthread_t id_output;
    pthread_t id_flist;
    pthread_t id_input;

    pthread_create(&id_head, NULL, run_head, (void*)&info);
    usleep(10000);
    pthread_create(&id_output, NULL, run_output, (void*)&info);
    usleep(10000);
    pthread_create(&id_flist, NULL, run_flist, (void*)&info);
    usleep(10000);
    pthread_create(&id_input, NULL, run_input, (void*)&info);

    pthread_join(id_head, NULL);
    pthread_join(id_output, NULL);
    pthread_join(id_flist, NULL);
    pthread_join(id_input, NULL);

    endwin();
    return 0;
}





