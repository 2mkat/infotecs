#ifndef SERVER_H
#define SERVER_H

#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class DataParser {
public:
    bool validStr(std::string &str);
    std::queue<char> strToKb(std::string &str);
};

class DataSender : public DataParser {
private:
    std::queue<char> buffer_;
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