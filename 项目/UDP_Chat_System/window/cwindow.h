#pragma once

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
using namespace std;

#define SIZE 1024

class cwindow
{
    public:
        cwindow();
        ~cwindow();

        void init();

        void create_head();
        void create_output();
        void create_flist();
        void create_input();
        
        static void put_str_to_win(WINDOW* win, int _y, int _x, const std::string& _str);
        static void get_str_from_win(WINDOW* win, std::string& _str);
        static void clr_win_line(WINDOW* win, int begin, int num);

        void refresh_win(WINDOW* win);

        WINDOW* get_win_head();
        WINDOW* get_win_output();
        WINDOW* get_win_flist();
        WINDOW* get_win_input();

    private:
        WINDOW* head;
        WINDOW* output;
        WINDOW* flist;
        WINDOW* input;
};
