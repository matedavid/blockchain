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
    coin->createAccount("wallet1");
    std::cout << coin->chain.size() << std::endl;
    coin->createAccount("wallet2");
    coin->addTransaction("wallet1", "wallet2", 10);
    coin->addTransaction("wallet2", "wallet1", 20);
    
    std::cout << coin-> checkBalance("wallet1") << " " << coin->checkBalance("wallet2") << std::endl;
    
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
