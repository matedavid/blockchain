//
//  main.cpp
//  BlockChain
//
//  Created by David Mate López on 21/03/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>

// Socket libraries
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>

// File inclues
#include "BlockChain.hpp"
#include "Block.hpp"
#include "NetCommunication.hpp"

#define PORT 8000

int createSocket() {
    // Creation of the socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // Initialization of address for server and for client connection
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;
    
    // Set to zero the rest of the values in address
    bzero(&(address.sin_zero), 8);
    
    // Bind to port and address specified in addres object
    if (bind(sock, (struct sockaddr*)&address, sizeof(struct sockaddr)) < 0) {
        perror("Error in bind");
        exit(-1);
    }
    
    // Start listening for requests
    if (listen(sock, 2) < 0) {
        perror("Error in listen");
        exit(-1);
    }
    
    return sock;
}



int main(int argc, const char * argv[]) {
    DNS *dns = new DNS();
    dns->getNodes();
    return 0;
}


/*
int main(int argc, const char * argv[]) {
    
    // Creation of the blockchain
    BlockChain *coin = new BlockChain();

    int sock = createSocket();
    struct sockaddr_in client;
    int sin_size;
    
    std::cout << "Listening for incoming requests..." << std::endl;
    
    // Infinite loop to listen for requests of wallets
    while (true) {
        sin_size = sizeof(struct sockaddr_in);
        int sockconn = accept(sock, (struct sockaddr*)&client, (socklen_t*)&sin_size);
        
        send(sockconn, "Welcome to the socket;", 22, 0);
        if (sockconn == -1) {
            perror("Error in accept");
            exit(-1);
        }
        
        // Infinite loop to listen for messages and send responses
        while (true) {
            const int n = 200;
            char buffer[n] = {0};
            recv(sockconn, &buffer, n, 0);
            
            printf("Recv: %s", buffer);
            
            // Manage communication options (example: addresses)
            std::vector<std::string> options;
            RequestSchema s = parseCommand(buffer, options);
            
            // Close connection if request type is exit
            if (s == EXIT) {
                printf("Closing connection...\n");
                close(sockconn);
                break;
            }
            
            std::string responseValue, res;
            ResponseSchema r = requestAction(coin, s, options, responseValue);
            
            if (r == REQUEST_INPUT_ERROR) {
                res = "REQUEST_INPUT_ERROR:;\n";
            } else if (r == NOT_ENOUGH_FUNDS) {
                res = "NOT_ENOUGH_FUNDS:;\n";
            } else if (r == COMMAND_NOT_FOUND) {
                res = "COMMAND_NOT_FOUND:;\n";
            } else if (r == ADDRESS_EXISTS) {
                res = "ADDRESS_EXISTS:;\n";
            } else if (r == SUCCESS) {
                res = "SUCCESS: " + responseValue + ";\n";
            }

            send(sockconn, res.c_str(), res.length(), 0);
            res.clear();
        }
    }
    return 0;
}
*/
