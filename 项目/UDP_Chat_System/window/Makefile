#DEBUG=-D_CWINDOW_MAIN_
cwindow:cwindow.cpp
	g++ -o $@ $^ -lncurses -static $(DEBUG)

.PHONY:clean
clean:
	rm -rf cwindow
