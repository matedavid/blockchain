//
//  BlockChain.cpp
//  BlockChain
//
//  Created by David Mate López on 21/03/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#include "BlockChain.hpp"


BlockChain::BlockChain() {
    Block *genesis = new Block(std::vector<Transaction>(), "00000", time(0));
    this->chain.push_back(*genesis);
}


void BlockChain::addBlock(std::vector<Transaction> transactions) {
    Block lastBlock = this->getLastBlock();
    this->chain.push_back(Block(transactions, lastBlock.hash, time(0)));
}

Block BlockChain::getLastBlock() {
    return this->chain[this->chain.size() - 1];
}


bool BlockChain::validateChain() {
    for (int i = 1; i < this->chain.size(); i++) {
        if (this->chain[i].prevHash.compare(this->chain[i-1].calculateHash()) != 0) {
            return false;
        } else if (this->chain[i].hash.compare(this->chain[i].calculateHash()) != 0) {
            return false;
        }
    }
    return true;
}


float BlockChain::checkBalance(std::string wallet) {
    float balance = 0.0f;
    for (int i = 0; i < this->chain.size(); i++) {
        for (int t = 0; t < this->chain[i].transactions.size(); t++) {
            Transaction currentTransaction = this->chain[i].transactions[t];
            if (currentTransaction.sender.compare(wallet) == 0) {
                balance -= currentTransaction.transaction;
            } else if (currentTransaction.receiver.compare(wallet) == 0) {
                balance += currentTransaction.transaction;
            }
        }
    }
    return balance;
}
