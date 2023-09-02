#include "server.h"

#include <cstring>
#include <iostream>


void Server::launchSocket() {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(1337);

    if (bind(sockfd, (const struct sockaddr *) &address,
                sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

void Server::RunReviewer() {
    recv(sockfd, &data, sizeof(int), MSG_WAITALL);
    if (data / 100 > 0 && data % 32 == 0) {
        std::cout << "Data received" << '\n';
    } else {
        std::cout << "Error with data receiving" << '\n';
    }
}