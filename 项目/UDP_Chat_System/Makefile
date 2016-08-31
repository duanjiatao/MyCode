ROOT_PATH=$(shell pwd)
SERVER=$(ROOT_PATH)/server
CLIENT=$(ROOT_PATH)/client
SER_CLI=$(SERVER) $(CLIENT)

.PHONY:output
output:
	@for dir in `echo $(SER_CLI)`;\
	do\
		cd $$dir;\
		make;\
		cd -;\
	done
	@mkdir output
	@cp $(SERVER)/udp_server output
	@cp $(CLIENT)/udp_client output
	@cp $(ROOT_PATH)/start_server.sh output
	@cp $(ROOT_PATH)/start_client.sh output


.PHONY:clean
clean:
	@rm -rf output
	@for dir in `echo $(SER_CLI)`;\
	do\
		cd $$dir;\
		make clean;\
		cd -;\
	done

