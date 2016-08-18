INCLUDE_PATH=-I/home/djt2016/Linux/HTTP/httpd/lib/include
LIB_PATH=-L/home/djt2016/Linux/HTTP/httpd/lib/lib
MYSQL_PATH=/home/djt2016/Linux/HTTP/httpd/mysql_connect

FLAGS=-lmysqlclient
DEBUG=-D_DEBUG_
CC=g++
WAY=-o

MYSQL_SRC=mysql_api.cpp
MATH_ADD_SRC=math_cgi.cpp
MATH_ADD_BIN=math_cgi
INSERT_SRC=my_insert_cgi.cpp
INSERT_BIN=my_insert_cgi
SELECT_SRC=my_select_cgi.cpp
SELECT_BIN=my_select_cgi

.PHONY:all
all:$(INSERT_BIN) $(SELECT_BIN) $(MATH_ADD_BIN)

$(INSERT_BIN):$(INSERT_SRC) $(MYSQL_PATH)/$(MYSQL_SRC)
	$(CC) $(WAY) $@ $^ $(INCLUDE_PATH) $(LIB_PATH) -I$(MYSQL_PATH) $(DEBUG) $(FLAGS) 
	
$(SELECT_BIN):$(SELECT_SRC) $(MYSQL_PATH)/$(MYSQL_SRC)
	$(CC) $(WAY) $@ $^ $(INCLUDE_PATH) $(LIB_PATH) -I$(MYSQL_PATH) $(DEBUG) $(FLAGS)

$(MATH_ADD_BIN):$(MATH_ADD_SRC)
	$(CC) $(WAY) $@ $^ 

.PHONY:clean
clean:
	rm -rf $(INSERT_BIN) $(SELECT_BIN) $(MATH_ADD_BIN)



