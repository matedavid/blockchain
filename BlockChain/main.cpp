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

#include "BlockChain.hpp"
#include "Block.hpp"

#define PORT 8000

int main(int argc, const char * argv[]) {
    
    BlockChain *coin = new BlockChain();
    
    coin->addBlock({Transaction("wallet1", "wallet2", 20.0f)});
    // std::cout << coin->validateChain() << std::endl;
    std::cout << "Balance of " << "wallet1: " << coin->checkBalance("wallet1") << std::endl;
    
    /*
    struct sockaddr sin6;
    
    int s = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&sin6, sizeof(sin6));
    
    if (s == 0) {
        perror("Socket failed");
    } else {
        std::cout << "Returned: " << s << std::endl;
    
    }
    */
    return 0;
}
