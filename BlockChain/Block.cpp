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
    this->hash = this->calculateHash();
}

std::string Block::calculateHash() {
    std::hash<std::string> hasher;
    
    size_t hash = hasher(this->prevHash + std::ctime(&this->timestamp));
    return std::to_string(hash);
}


