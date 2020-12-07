# Simple-Blockchain

### Compile:
To compile the code, you need to install Cmake version 2.8 or higher, and have a c++ compiler installed. Then, follow these simple steps:
1. Create `build/` directory and cd into it
2. Run `cmake ..` inside the `build/` directory
3. Run `make` in the same directory as the second step.
4. Run `./blockchain` and the program will start running and listening for requests.

TODO: Document steps for compiling and staring DnsServer (still not implemented).

### Usage with Wallet:
Download the python local wallet from [here](https://github.com/matedavid/blockchain_wallet) 

### Use: 
Communicate using your computer terminal:
- MacOS / Linux: ```nc IP PORT``` example: ```nc localhost 8000```
- Windows: ```telnet IP PORT``` example: ```telnet localhost 8000```

### Wallet - Blockchain communication schema 
Global schema: ```<Command schema>: [option 1]; [option 2]; ...```
#### Schemas:
- ```EXIT:;```
    - **Description:** asks the blockchain to close connections
    - **Return:** always SUCCESS:;

- ```GET_BALANCE: address;```
    - **Description:** gets the balance of specified address
    - **Return:**
        - ```REQUEST_INPUT_ERROR:;``` if addres does not exist
        - ```SUCCESS:;``` if all Ok

- ```CREATE_TRANSACTION: sender; receiver; amount;```
    - **Description:** sends transaction with specified amount from address of sender to address of receiver
    - **Return:**
        - ```REQUEST_INPUT_ERROR:;``` if some of the two addresses does not exist
        - ```NOT_ENOUGH_FUNDS:;``` if the sender address does not have enough funds to send the amount
        - ```SUCCESS:;``` if all Ok
    
- ```CREATE_ADDRESS: address;```
    - **Description:** creates a new account with specified address
    - **Return:**
        - ```REQUEST_INPUT_ERROR:;``` if address is not correct
        - ```ADDRESS_EXISTS:;``` if the specified address already has an account
        - ```SUCCESS:;``` if all Ok

