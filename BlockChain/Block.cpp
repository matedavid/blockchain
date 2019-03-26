//
//  Block.cpp
//  BlockChain
//
//  Created by David Mate on 21/03/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#include "Block.hpp"

Block::Block(std::vector<Transaction> transactions, std::string prevHash, time_t timestamp) {
    this->transactions = transactions;
    this->prevHash = prevHash;
    this->timestamp = timestamp;
    this->difficulty = 2;
    this->hash = this->calculateHash();
}

std::string Block::calculateHash() {
    int nonce = 0;
    
    std::string input = this->prevHash + std::ctime(&this->timestamp) + this->getTransactionString();
    std::string hash; // = sha256(input);
    
    while (true) {
        hash = sha256(std::to_string(nonce) + input);
        bool ok = true;
        
        // The difficulty defines the number of '0's that the hash needs to have in front
        // This are calculated by adding the nonce
        for (int i = 0; i < this->difficulty; i++) {
            if (hash[i] != '0') {
                ok = false;
                break;
            }
        }
        
        if (ok)
            break;
        
        nonce += 1;
    }
    
    return hash;
}

std::string Block::convertSizeTString(size_t toConvert) {
    return std::to_string(toConvert);
}

std::string Block::getTransactionString() {
    std::string transactionString;
    int value = 0;
    for (int i = 0; i < transactions.size(); i++) {
        // Add the total value of all the transactiosn in the Block
        value += transactions[i].transaction;
        
        // Get both addresses of the transaction and concadenate them in one single string
        transactionString += transactions[i].sender + transactions[i].receiver;
    }
    
    return std::to_string(value) + transactionString;
}
