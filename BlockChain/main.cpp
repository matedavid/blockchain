//
//  main.cpp
//  BlockChain
//
//  Created by David Mate López on 21/03/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#include <iostream>
#include <sys/socket.h>
#include <string>
#include <ctime>

// Socket libraries include
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "BlockChain.hpp"
#include "Block.hpp"

#define PORT 8000

// Request reponse schema for communication between wallet and server (blockchain)
enum ReponseSchema { EXIT, GET_BALANCE, CREATE_TRANSACTION };

// Parse the commands from wallet to do the necessary action in the blockchain
ReponseSchema parseCommand(char* comm[]) {
    ReponseSchema s = EXIT;
    std::cout << comm << std::endl;
    return s;
}

int main(int argc, const char * argv[]) {
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int sin_size;
    
    // Initialization of address for server and for client connection
    struct sockaddr_in address, client;
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
    if (listen(sock, 2) == -1) {
        perror("Error in listen");
        exit(-1);
    }
    
    std::cout << "Listening for incoming requests..." << std::endl;
    
    // Infinite loop to listen for requests of wallets
    while (true) {
        sin_size = sizeof(struct sockaddr_in);
        int sockconn = accept(sock, (struct sockaddr*)&client, (socklen_t*)&sin_size);
        
        send(sockconn, "Welcome to the socket\n", 22, 0);
        if (sockconn == -1) {
            perror("Error in accept");
            exit(-1);
        }
        
        // Infinite loop to listen for messages and send responses
        while (true) {
            char buffer[8] = {0};
            recv(sockconn, &buffer, 8, 0);
            
            printf("Recv: %s", buffer);
            
            if (strcmp(buffer, "exit\n") == 0) {
                printf("Closing connection...\n");
                close(sockconn);
                break;
            }
        }
    }
    return 0;
    
    
    
    /*
    BlockChain *coin = new BlockChain();
    
    coin->createAccount("wallet1");
    coin->createAccount("wallet2");
    
    coin->chain[1].transactions[0].transaction = 200.0f;
    
    coin->addTransaction("wallet1", "wallet2", 50);
    
    std::cout << coin->checkBalance("wallet1") << " " << coin->checkBalance("wallet2") << std::endl;
    
    struct sockaddr sin6;
    
    int s = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&sin6, sizeof(sin6));
    
    if (s == 0) {
        perror("Socket failed");
    } else {
        std::cout << "Returned: " << s << std::endl;
    
    }
    */
}
