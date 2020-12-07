//
//  NetCommunication.hpp
//  BlockChain
//
//  Created by David Mate on 05/04/2019.
//  Copyright © 2019 David Mate. All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "HTTPRequest.h"

#include "BlockChain.h"
#include "Block.h"

// Request schema for communication between wallet to server
enum RequestSchema { EXIT, GET_BALANCE, CREATE_TRANSACTION, CREATE_ADDRESS, NONE = -1 };

// Response shema for cummunication from server to wallet
enum ResponseSchema { REQUEST_INPUT_ERROR = -1, COMMAND_NOT_FOUND = -2, NOT_ENOUGH_FUNDS = -3, ADDRESS_EXISTS = -4, SUCCESS = 0 };

// Command parsing and requests
RequestSchema parseCommand(char comm[], std::vector<std::string> &options);
ResponseSchema requestAction(BlockChain *coin, RequestSchema req, std::vector<std::string> &options, std::string &responseValue);