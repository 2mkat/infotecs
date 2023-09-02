#ifndef CLIENT_H
#define CLIENT_H

#pragma once

#include <string>
#include <mutex>
#include <condition_variable>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class DataParser {
public:
    bool validStr(std::string &str);
    void strToKb(std::string &str);
};

class DataSender : public DataParser {
private:
    std::string buffer_;
    std::mutex mu_;
    std::condition_variable cond_;
    bool isReady_ = false;
    int sockfd;
    struct sockaddr_in address;

    void launchSocket();

public:
    void runTask();
    void runSender();
};

#endif