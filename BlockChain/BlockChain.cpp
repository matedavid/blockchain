//
//  BlockChain.cpp
//  BlockChain
//
//  Created by David Mate López on 21/03/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#include "BlockChain.hpp"


BlockChain::BlockChain() {
    Block *genesis = new Block({Transaction("00000", "coin", 10000000.0f)}, "00000", time(0));
    this->chain.push_back(*genesis);
    copyChain = chain;
}

void BlockChain::addBlock(std::vector<Transaction> transactions) {
    Block lastBlock = this->getLastBlock();
    
    if (validateChain()) {
        if (lastBlock.hash.compare(lastBlock.calculateHash()) == 0)
            this->chain.push_back(Block(transactions, lastBlock.hash, time(0)));
        copyChain = chain;
    } else {
        std::cout << "Chain not valid" << std::endl;
        recuperateChain();
        addBlock(transactions);
    }
}

Block BlockChain::getLastBlock() {
    return this->chain[this->chain.size() - 1];
}


void BlockChain::createAccount(std::string address) {
    if (checkAddress(address) == false) {
        pendingTransactions.push_back(Transaction("coin", address, 100.0f));
        
        // The user should wait until the transaction is accepted, but for the sake of not doing a lot of transactions I will add the block rith away
        addBlock(pendingTransactions);
        pendingTransactions = {};
    }
}

void BlockChain::addTransaction(std::string sender, std::string receiver, float amount) {
    if (validateChain() == false) {
        recuperateChain();
    }
    if (checkAddress(sender) == false || checkAddress(receiver) == false) {
        std::cout << "One of the accounts doesen't exist" << std::endl;
        return;
    }
    
    if (checkBalance(sender) >= amount) {
        Transaction trans = Transaction(sender, receiver, amount);
        pendingTransactions.push_back(trans);
    }
    if (pendingTransactions.size() >= 1) { // the amount should be bigger, somehing like 5, but for the sake of waiting... 
        addBlock(pendingTransactions);
        pendingTransactions = {};
    }
}


bool BlockChain::validateChain() {
    // NOTE: Could do the recuperate chain and this function together, but better to have them so i can use them separately
    for (int i = 1; i < this->chain.size(); i++) {
        if (chain[i].prevHash.compare(chain[i-1].calculateHash()) != 0) {
            std::cout << "Not equal: " << chain[i].prevHash << " - " << chain[i-1].calculateHash() << std::endl;
            return false;
        } else if (chain[i].hash.compare(chain[i].calculateHash()) != 0) {
            std::cout << "Not equal: " << chain[i].hash << " - " << chain[i].calculateHash() << std::endl;
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

bool BlockChain::checkAddress(std::string address) {
    for (int i = 0; i < chain.size(); i++) {
        for (int t = 0; t < chain[i].transactions.size(); t++) {
            if (chain[i].transactions[t].sender.compare(address) == 0 || chain[i].transactions[t].receiver.compare(address) == 0) {
                return true;
            }
        }
    }
    return false;
}

void BlockChain::recuperateChain() {
    std::cout << "Recuperating last saved chain..." << std::endl;
    chain = copyChain;
}

