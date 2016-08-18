//httpd.h
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define _MAX_LISTEN_ 5
#define _SIZE_ 1024
#define INDEX_PAGE "index.html"
//#define INDEX_PAGE "begining.mp4"
//#define INDEX_PAGE "index2.html"
#define HTTP_VERSION "HTTP/1.0"
