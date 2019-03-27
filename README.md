# Local blockchain based on bitcoin

### Wallet - Blockchain communication schema 
Global schema: ```<Command schema>: [options]```
##### Command Schema:
* ```EXIT```: terminates the connection between the wallet and the blockchain
* ```GET_BALANCE```: asks for the ballance of the wallet of specific address
* ```CREATE_TRANSACTION```: creates a transaction

##### Options:
* Exit: No options
* GET_BALANCE: 
  * <address>: the addres of the account to check the balance
* CREATE_TRANSACTION:
  * <sender>: the address of the account to send the coins from 
  * <receiver>: the address of the account to send the coins to

