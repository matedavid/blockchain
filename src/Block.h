//
//  Block.hpp
//  BlockChain
//
//  Created by David Mate on 21/03/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <functional>

#include "sha256.h"

class Transaction {
public: // private
    std::string sender, receiver;
    float transaction;
    time_t timestamp;
public:
    Transaction(std::string sender, std::string receiver, float transaction) : sender(sender), receiver(receiver), transaction(transaction), timestamp(time(0)) { };
};

class Block {
public: // private
    std::vector<Transaction> transactions;
    time_t timestamp;
    std::string hash;
    std::string prevHash;
    int difficulty;
    
public:
    Block(std::vector<Transaction> transactions, std::string prevHash, time_t timestamp);
    std::string computeHash();
    std::string convertSizeTString(size_t toConvert);
    std::string getTransactionString();
};

