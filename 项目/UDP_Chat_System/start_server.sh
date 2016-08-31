#!/bin/bash

UDP_SERVER="udp_server"
SERVER_PATH="`pwd`/server"
IP="127.0.0.1"
PORT="9999"
START="./${UDP_SERVER} ${IP} ${PORT}"


if [ -d ${SERVER_PATH} ]
then
    for server in "`cd ${SERVER_PATH}`"
    do
        if [ $server==${UDP_SERVER} ]
        then
            START="${SERVER_PATH}/${UDP_SERVER} ${IP} ${PORT}"
            break
        fi
    done
fi

${START}
