#ifndef CLIENT_H
#define CLIENT_H

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class Server {
    int data;
    int sockfd;
    struct sockaddr_in address;

public:
    void launchSocket();
    void RunReviewer();
};

#endif
