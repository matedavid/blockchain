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

// Request schema for communication between wallet to server
// TODO: Implement CREATE_ADDRESS schema method
enum RequestSchema { EXIT, GET_BALANCE, CREATE_TRANSACTION, CREATE_ADDRESS, NONE = -1 };

// Response shema for cummunication from server to wallet
enum ResponseSchema { REQUEST_INPUT_ERROR = -1, COMMAND_NOT_FOUND = -2, NOT_ENOUGH_FUNDS = -3, SUCCESS = 0 };

// Parse the commands from wallet to do the necessary action in the blockchain
RequestSchema parseCommand(char comm[], std::vector<std::string> &options) {
    RequestSchema s;
    std::string command, commStr = comm;
    int commandPos = 0;
    
    // Get primary command
    for (int i = 0; i < commStr.length(); i++) {
        if (commStr[i] == ':') {
            commandPos = i+1;
            break;
        }
        command += commStr[i];
    }
    
    // Get options if they are
    std::string currentOption;
    for (int c = commandPos; c < commStr.length(); c++) {
        if (commStr[c] == ';') {
            options.push_back(currentOption);
            currentOption = {'\0'};
            continue;
        } else if (commStr[c] == ' ') {
            continue;
        }
        currentOption += commStr[c];
    }
    
    if (command.compare("EXIT") == 0) {
        s = EXIT;
    } else if (command.compare("GET_BALANCE") == 0) {
        s = GET_BALANCE;
    } else if (command.compare("CREATE_TRANSACTION") == 0) {
        s = CREATE_TRANSACTION;
    } else {
        s = NONE;
    }
    
    return s;
}

ResponseSchema requestAction(BlockChain *coin, RequestSchema req, std::vector<std::string> &options, std::string &responseValue) {
    ResponseSchema r;
    
    coin->createAccount("3333");
    
    switch (req) {
        case GET_BALANCE:
            r = REQUEST_INPUT_ERROR;
            if (options.size() > 0) {
                if (coin->checkAddress(options[0])) {
                    float balance = coin->checkBalance(options[0]);
                    r = SUCCESS;
                    responseValue = std::to_string(balance);
                }
            }
            break;
            
        case CREATE_TRANSACTION:
            if (options.size() > 2) {
                if (coin->checkAddress(options[0]) && coin->checkAddress(options[1])) {
                    float amount = (float)stof(options[2]);
                    
                    if (coin->checkBalance(options[0]) >= amount) {
                        responseValue = std::to_string(coin->checkBalance(options[0])) + ";";
                        r = SUCCESS;
                    } else {
                        r = NOT_ENOUGH_FUNDS;
                    }
                } else {
                    r = REQUEST_INPUT_ERROR;
                }
            } else {
                r = REQUEST_INPUT_ERROR;
            }
            
            break;
        default:
            r = COMMAND_NOT_FOUND;
            break;
    }
    return r;
}

int main(int argc, const char * argv[]) {
    
    BlockChain *coin = new BlockChain();
    
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
    if (listen(sock, 2) < 0) {
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
            const int n = 128;
            char buffer[n] = {0};
            recv(sockconn, &buffer, n, 0);
            
            printf("Recv: %s", buffer);
            
            // Manage communication options (example: addresses)
            std::vector<std::string> options;
            RequestSchema s = parseCommand(buffer, options);
            
            if (s == EXIT) {
                printf("Closing connection...\n");
                close(sockconn);
                break;
            }
            
            std::string responseValue;
            ResponseSchema r = requestAction(coin, s, options, responseValue);
            
            if (r == REQUEST_INPUT_ERROR) {
                std::string res = "REQUEST_INPUT_ERROR:;\n";
                send(sockconn, res.c_str(), sizeof(res), 0);
            } else if (r == NOT_ENOUGH_FUNDS) {
                std::string res = "NOT_ENOUGH_FUNDS:;\n";
                send(sockconn, res.c_str(), sizeof(res), 0);
            } else if (r == COMMAND_NOT_FOUND) {
                std::string res = "COMMAND_NOT_FOUND:;\n";
                send(sockconn, res.c_str(), sizeof(res), 0);
            } else if (r == SUCCESS) {
                std::string res = "SUCCESS: " + responseValue + ";\n";
                send(sockconn, res.c_str(), sizeof(res), 0);
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
    */
}
