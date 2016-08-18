ROOT_PATH=$(shell pwd)
INCLUDE_PATH=-I$(ROOT_PATH)/../lib/include
LIB_PATH=-L$(ROOT_PATH)/../lib/lib
FLAGS=-lmysqlclient
CC=g++
SRC=mysql_api.cpp
BIN=mysql_api
DEBUG=-D_DEBUG_

$(BIN):$(SRC)
	$(CC) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(FLAGS) $(DEBUG)

.PHONY:clean
clean:
	rm -rf $(BIN)
 

