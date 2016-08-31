ROOT_PATH=$(shell pwd)
DATAPOOL_PATH=$(ROOT_PATH)/../data_pool
COMM_PATH=$(ROOT_PATH)/../comm

SERVER=udp_server
CC=g++
LDFLAGS=-lpthread -ljsoncpp  -static

SRC=$(shell ls *.cpp)
SRC+=$(shell cd $(DATAPOOL_PATH); ls *.cpp)
SRC+=$(shell cd $(COMM_PATH); ls *.cpp)
OBJ=$(SRC:.cpp=.o)

INCLUDE=-I$(DATAPOOL_PATH) -I$(COMM_PATH) -I$(ROOT_PATH)/../lib/include
LIB=-L$(ROOT_PATH)/../lib/lib

$(SERVER):$(OBJ) 
	$(CC) -o $@ $^ $(LIB) $(LDFLAGS)
%.o:%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(DATAPOOL_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(COMM_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE)

.PHONY:clean
clean:
	rm -rf $(SERVER) *.o

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SRC)
	@echo $(OBJ)
