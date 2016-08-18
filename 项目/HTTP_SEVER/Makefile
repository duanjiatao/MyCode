ROOT_PATH=$(shell pwd)
CGI_PATH=$(ROOT_PATH)/htdoc/cgi_bin

SRC=httpd.c
BIN=httpd
CC=gcc
FLAGS=-o
DEBUG=-D_DEBUG_
LDFLAGS=-lpthread #-static

.PHONU:all
all:$(BIN) cgi

$(BIN):$(SRC)
	$(CC) $(FLAGS) $@ $^ $(LDFLAGS) $(DEBUG) 

.PHONY:cgi
cgi:
	for name in `echo $(CGI_PATH)`;\
	do\
		cd $$name;\
		make;\
		cd -;\
	done

.PHONY:clean
clean:
	rm -rf $(BIN) output
	for name in `echo $(CGI_PATH)`;\
	do\
		cd $$name;\
		make clean;\
		cd -;\
	done

.PHONY:output
output:
	mkdir -p output/lib/lib
	mkdir -p output/htdoc/image
	mkdir -p output/htdoc/cgi_bin
	cp -f httpd output
	cp htdoc/favicon.ico output/htdoc
	cp htdoc/index.html output/htdoc
	cp htdoc/image/* output/htdoc/image
	cp htdoc/cgi_bin/math_cgi output/htdoc/cgi_bin
	cp htdoc/cgi_bin/my_insert_cgi output/htdoc/cgi_bin
	cp htdoc/cgi_bin/my_select_cgi output/htdoc/cgi_bin
	cp lib/lib/* output/lib/lib
	cp start.sh output
