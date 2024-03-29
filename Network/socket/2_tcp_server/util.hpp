#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"


#define SOCKET_ERR 1
#define BIND_ERR   2
#define LISTEN_ERR 3
#define BUFFER_SIZE 1024
#define USAGE_ERR  4
#define CONN_ERR   5