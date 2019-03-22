//
//  BlockChain.hpp
//  BlockChain
//
//  Created by David Mate López on 21/03/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "Block.hpp"

class BlockChain {
public: // private
    std::vector<Block> chain;
    std::vector<Transaction> pendingTransactions;
public:
    BlockChain();
    void addBlock(std::vector<Transaction> transactions);
    void addTransaction(std::string sender, std::string receiver, float amount);
    void createAccount(std::string address);
    Block getLastBlock();
    bool validateChain();
    float checkBalance(std::string wallet);
    bool checkAddress(std::string account);
};
