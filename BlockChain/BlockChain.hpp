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
private:
    std::vector<Block> chain;
public:
    BlockChain();
    void addBlock(std::vector<Transaction> transactions);
    Block getLastBlock();
    bool validateChain();
    float checkBalance(std::string wallet);
};
