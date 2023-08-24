#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstring>
#include <iostream>

class Server {
    int dataLength;
    int sockfd;
    struct sockaddr_in address;

public:
    void launchSocket() {
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&address, 0, sizeof(address));

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(1234);

        // назначаем порт сокету
        if (bind(sockfd, (const struct sockaddr *) &address,
                 sizeof(address)) < 0) {
            perror("Bind failed");
            exit(EXIT_FAILURE);
        }
    }

    void RunReviewer() {
        recv(sockfd, &dataLength, sizeof(int), MSG_WAITALL);
        if (dataLength / 100 > 0 && dataLength % 32 == 0) {
            std::cout << "Data received" << '\n';
        } else {
            std::cout << "Error with data receiving" << '\n';
        }
    }

    // ~Server() {

    // }
};

int main() {
    Server ser;
    ser.launchSocket();
    try {
        while (true) {
            ser.RunReviewer();
        }
    }
    catch (std::exception &ex) {
        std::cout << ex.what() << '\n';
    }

    return 0;
}
