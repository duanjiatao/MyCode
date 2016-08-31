#!/bin/bash

UDP_CLIENT="udp_client"
CLIENT_PATH="`pwd`/client"
IP="127.0.0.1"
PORT="9999"
START="./${UDP_CLIENT} ${IP} ${PORT}"


if [ -d ${CLIENT_PATH} ]
then
    for client in "`cd ${CLIENT_PATH}`"
    do
        if [ $client==${UDP_CLIENT} ]
        then
            START="${CLIENT_PATH}/${UDP_CLIENT} ${IP} ${PORT}"
            break
        fi
    done
fi

${START}
