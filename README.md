# Local blockchain based on bitcoin

### Use:
Download the python local wallet from [here](https://github.com/matedavid/blockchain_wallet) 

Communicate using your computer terminal:
- MacOS / Linux: ```nc IP PORT``` example: ```nc localhost 8000```
- Windows: ```telnet IP PORT``` example: ```telnet localhost 8000```

### Wallet - Blockchain communication schema 
Global schema: ```<Command schema>: [option 1]; [option 2]; ...```
###### Schemas:
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
        - ```REQUEST_INPUT_ERROR:;``` if address if address is not correct
        - ```ADDRESS_EXISTS:;``` if the specified address already has an account
        - ```SUCCESS:;``` if all Ok
