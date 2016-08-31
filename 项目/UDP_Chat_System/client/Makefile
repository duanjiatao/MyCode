ROOT_PATH=$(shell pwd)
DATAPOOL_PATH=$(ROOT_PATH)/../data_pool
COMM_PATH=$(ROOT_PATH)/../comm
WINDOW_PATH=$(ROOT_PATH)/../window

CLIENT=udp_client
CC=g++
LDFLAGS=-lpthread -ljsoncpp -lncurses  -static

SRC=$(shell ls *.cpp)
SRC+=$(shell cd $(DATAPOOL_PATH); ls *.cpp)
SRC+=$(shell cd $(COMM_PATH); ls *.cpp)
SRC+=$(shell cd $(WINDOW_PATH); ls *.cpp)
OBJ=$(SRC:.cpp=.o)

INCLUDE=-I$(DATAPOOL_PATH) -I$(COMM_PATH) -I$(WINDOW_PATH) -I$(ROOT_PATH)/../lib/include
LIB=-L$(ROOT_PATH)/../lib/lib

$(CLIENT):$(OBJ) 
	$(CC) -o $@ $^ $(LIB) $(LDFLAGS)
%.o:%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(DATAPOOL_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(COMM_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(WINDOW_PATH)/%.cpp
	$(CC) -c $< $(INCLUDE)

.PHONY:clean
clean:
	rm -rf $(CLIENT) *.o

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SRC)
	@echo $(OBJ)
