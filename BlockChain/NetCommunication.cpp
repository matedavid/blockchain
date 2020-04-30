//
//  NetCommunication.cpp
//  BlockChain
//
//  Created by David Mate on 05/04/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#include "NetCommunication.hpp"

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
            currentOption.clear();
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
    } else if (command.compare("CREATE_ADDRESS") == 0) {
        s = CREATE_ADDRESS;
    } else {
        s = NONE;
    }
    
    return s;
}

// Do the action given request schema
ResponseSchema requestAction(BlockChain *coin, RequestSchema req, std::vector<std::string> &options, std::string &responseValue) {
    ResponseSchema r;
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
            if (options.size() == 3) {
                std::cout << coin->checkAddress(options[0]) << " " << options[1] << ": " << coin->checkAddress(options[1]) << std::endl;
                if (coin->checkAddress(options[0]) && coin->checkAddress(options[1])) {
                    float amount = (float)stof(options[2]);
                    
                    if (coin->checkBalance(options[0]) >= amount) {
                        coin->addTransaction(options[0], options[1], amount);
                        responseValue = std::to_string(coin->checkBalance(options[0]));
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
            
        case CREATE_ADDRESS:
            if (options.size()) {
                if (!coin->checkAddress(options[0]) && options[0].length() == 66) {
                    responseValue = "Creating wallet";
                    coin->createAccount(options[0]);
                    r = SUCCESS;
                } else {
                    // responseValue = "Address already exists";
                    r = (options[0].length() != 66) ? REQUEST_INPUT_ERROR : ADDRESS_EXISTS;
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


std::vector<Node> DNS::getNodes() {
    http::Request request(this->address+"api/getNodes");
    const http::Response response = request.send("GET");
    std::string res = std::string(response.body.begin(), response.body.end());
    std::cout << "Complete: " << res << std::endl;
    
    // Get all nodes
    std::vector<Node> nodes;
    
    std::vector<std::string> currentNode;
    std::string currentValue;
    for (int i = 0; i < res.length(); i++) {
        if (res[i] == ',') {
            currentNode.push_back(currentValue);
            currentValue.clear();
            i++;
        } else if (res[i] == ';') {
            currentNode.push_back(currentValue);
            currentValue.clear();

            Node node = { currentNode.at(0), currentNode.at(1), currentNode.at(2) };
            nodes.push_back(node);
            currentNode.clear();
            i++;
        }
        currentValue += res[i];
    }
    
    for (int e = 0; e < nodes.size(); e++) {
        Node node = nodes.at(e);
        std::cout << node.header << " " << node.online << " " << node.last_connected << std::endl;
    }
    
    return nodes;
}


void DNS::sendNode() {  }
