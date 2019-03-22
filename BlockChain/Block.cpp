//
//  Block.cpp
//  BlockChain
//
//  Created by David Mate López on 21/03/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#include "Block.hpp"

Block::Block(std::vector<Transaction> transactions, std::string prevHash, time_t timestamp) {
    this->transactions = transactions;
    this->prevHash = prevHash;
    this->timestamp = timestamp;
    // this->hash = this->calculateHash();
}

std::string Block::calculateHash() {
    int diff = 2;
    int nonce = 0;
    
    std::string input = this->prevHash + std::ctime(&this->timestamp);
    std::string hash = sha256(input);
    // std::cout << hash << std::endl;
    
    while (true) {
        hash = sha256(std::to_string(nonce) + input);
        bool ok = true;
        for (int i = 0; i < diff; i++) {
            if (hash[i] != '0') {
                ok = false;
                break;
            }
        }
        
        if (ok)
            break;
        nonce += 1;
    }
    
    // std::cout << hashString << ": " << hashString[0] << ", " << hashString[1] << std::endl;
    return hash;
}

std::string Block::convertSizeTString(size_t toConvert) {
    return std::to_string(toConvert);
}
