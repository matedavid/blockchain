//
//  Block.hpp
//  BlockChain
//
//  Created by David Mate López on 21/03/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <functional>

class Transaction {
public: // private
    std::string sender, receiver;
    float transaction;
public:
    Transaction(std::string sender, std::string receiver, float transaction) : sender(sender), receiver(receiver), transaction(transaction) { };
};

class Block {
public: // private
    std::vector<Transaction> transactions;
    time_t timestamp;
    std::string hash;
    std::string prevHash;
    std::string nonce;
    
public:
    Block(std::vector<Transaction> transactions, std::string prevHash, time_t timestamp);
    std::string calculateHash();
};
