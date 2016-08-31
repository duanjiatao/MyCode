#include "cwindow.h"

cwindow::cwindow()
    :head(NULL)
    ,output(NULL)
    ,flist(NULL)
    ,input(NULL)
{
    this->init();
}

void cwindow::init()
{
    initscr();
}

cwindow::~cwindow()
{
    endwin();
}

void cwindow::create_head()
{
    int _h = LINES/5;
    int _w = COLS;
    int _y = 0;
    int _x = 0;
    head = newwin(_h, _w, _y, _x);
}

void cwindow::create_output()
{
    int _h = LINES*3/5;
    int _w = COLS*3/4;
    int _y = LINES/5;
    int _x = 0;
    output = newwin(_h, _w, _y, _x);
}

void cwindow::create_flist()
{
    int _h = LINES*3/5;
    int _w = COLS/4;
    int _y = LINES/5;
    int _x = COLS*3/4;
    flist = newwin(_h, _w, _y, _x);
}

void cwindow::create_input()
{
    int _h = LINES/5;
    int _w = COLS;
    int _y = LINES*4/5;
    int _x = 0;
    input = newwin(_h, _w, _y, _x);
}

void cwindow::put_str_to_win(WINDOW* win, int _y, int _x,\
        const std::string& _str)
{
    mvwaddstr(win, _y, _x, _str.c_str());
}

void cwindow::get_str_from_win(WINDOW* win, std::string& _str)
{
    char buf[SIZE];
    memset(buf, '\0', sizeof(buf));
    wgetnstr(win, buf, sizeof(buf));
    _str = buf;
}

void cwindow::clr_win_line(WINDOW* win, int begin, int num)
{
    while(num-- > 0)
    {
        wmove(win, begin++, 0);
        wclrtoeol(win);
    }
}

void cwindow::refresh_win(WINDOW* win)
{
    box(win, 0 ,0);
    wrefresh(win);
}

WINDOW* cwindow::get_win_head()
{
    return head;
}

WINDOW* cwindow::get_win_output()
{
    return output;
}

WINDOW* cwindow::get_win_flist()
{
    return flist;
}

WINDOW* cwindow::get_win_input()
{
    return input;
}

#ifdef _CWINDOW_MAIN_
int main()
{
    cwindow cw;

    cw.create_head();
    cw.refresh_win(cw.get_win_head());
    sleep(1);

    cw.create_output();
    cw.refresh_win(cw.get_win_output());
    sleep(1);

    cw.create_flist();
    cw.refresh_win(cw.get_win_flist());
    sleep(1);

    cw.create_input();
    cw.refresh_win(cw.get_win_input());
    sleep(10);

    return 0;
}
#endif









