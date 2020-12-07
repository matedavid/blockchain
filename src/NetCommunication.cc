#include "NetCommunication.h"

// Parse the commands from wallet to do the necessary action in the blockchain
RequestSchema parseCommand(char comm[], std::vector<std::string> &options) {
    RequestSchema s;
    std::string command, commStr = comm;
    int commandPos = 0;
    
    // Get primary command
    for (int i = 0; i < commStr.length(); i++) {
        if (commStr[i] == ':') {
            commandPos = i+1;
            break;
        }
        command += commStr[i];
    }
    
    // Get options if there are
    std::string currentOption;
    for (int c = commandPos; c < commStr.length(); c++) {
        if (commStr[c] == ';') {
            options.push_back(currentOption);
            currentOption.clear();
            continue;
        } else if (commStr[c] == ' ') {
            continue;
        }
        currentOption += commStr[c];
    }
    
    if (command.compare("EXIT") == 0) s = EXIT;
    else if (command.compare("GET_BALANCE") == 0) s = GET_BALANCE;
    else if (command.compare("CREATE_TRANSACTION") == 0) s = CREATE_TRANSACTION;
    else if (command.compare("CREATE_ADDRESS") == 0) s = CREATE_ADDRESS;
    else s = NONE;

    return s;
}

// Do the action given request schema
ResponseSchema requestAction(BlockChain *coin, RequestSchema req, std::vector<std::string> &options, std::string &responseValue) {
    ResponseSchema r;
    switch (req) {
        case GET_BALANCE:
            r = REQUEST_INPUT_ERROR;
            if (options.size() > 0 and coin->checkAddress(options[0])) {
                float balance = coin->checkBalance(options[0]);
                r = SUCCESS;
                responseValue = std::to_string(balance);
            }
            break;

        case CREATE_TRANSACTION:
			if (options.size() != 3)
				r = REQUEST_INPUT_ERROR;
			else if (!coin->checkAddress(options[0]) || !coin->checkAddress(options[1]))
				r = REQUEST_INPUT_ERROR;
			else {
				float amount = (float)stof(options[2]);
				if (coin->checkBalance(options[0]) < amount) {
					r = NOT_ENOUGH_FUNDS;
					break;
				}

				coin->addTransaction(options[0], options[1], amount);
				responseValue = std::to_string(coin->checkBalance(options[0]));
				r = SUCCESS;
			}
			break;

        case CREATE_ADDRESS:
			if (!options.size() || options[0].length() != 66)
				r = REQUEST_INPUT_ERROR;
			else if (coin->checkAddress(options[0])) 
				r = ADDRESS_EXISTS;
			else {
                responseValue = "Creating wallet";
                coin->createAccount(options[0]);
                r = SUCCESS;
			}
			break;

        default:
            r = COMMAND_NOT_FOUND;
            break;
    }
    return r;
}

