cmake_minimum_required(VERSION 2.8)
project(BlockChain)

set(CMAKE_CXX_STANDARD 11)

include_directories(test PRIVATE Blockchain/include BlockChain/lib)
set(SOURCES "BlockChain/src/main.cc" "BlockChain/lib/sha256.cc" 
            "BlockChain/src/Block.cc" "BlockChain/src/BlockChain.cc" 
            "BlockChain/src/NetCommunication.cc" "BlockChain/src/Dns.cc")
add_executable(bin/blockchain ${SOURCES})