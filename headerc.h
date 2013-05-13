#ifndef HEADERC_H
#define HEADERC_H

#define _GNU_SOURCE
//for strcasestr

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <pthread.h>
#include <sys/mman.h>

#define SA struct sockaddr

#define FATAL(msg) do{exit(-1);} while(0)

#endif
