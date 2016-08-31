ROOT_PATH=$(shell pwd)
INCLUDE=-I$(ROOT_PATH)/../lib/include
LIB=-L$(ROOT_PATH)/../lib/lib
#INCLUDE=-I/home/djt2016/package/jsoncpp-src-0.5.0/include
#LIB=-L/home/djt2016/package/jsoncpp-src-0.5.0/libs/linux-gcc-4.8.5
LDFLAGS=-ljsoncpp
DEBUG1=-D_MY_JSON_MAIN_
DEBUG2=-D_UDP_DATA_MAIN_

#my_json:my_json.cpp
#	g++ -o $@ $^ $(INCLUDE) $(LIB) $(LDFLAGS) $(DEBUG1)


udp_data:udp_data.cpp my_json.cpp
	g++ -o $@ $^ $(INCLUDE) $(LIB) $(LDFLAGS) $(DEBUG2)

#udp_data:udp_data.o my_json.o
#	g++ -o $@ $^ $(LIB) $(LDFLAGS)
#udp_data.o:udp_data.cpp
#	g++ -c $< $(INCLUDE)
#my_json.o:my_json.cpp
#	g++ -c $< $(INCLUDE)


.PHONY:clean
clean:
	rm -rf my_json udp_data *.o
