cmake_minimum_required(VERSION 3.8)

set(project_name blockchain)
project(${project_name} CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB SOURCES "src/*cc")

#set(SOURCES "BlockChain/src/main.cc" "BlockChain/lib/sha256.cc" 
#"BlockChain/src/Block.cc" "BlockChain/src/BlockChain.cc" 
#"BlockChain/src/NetCommunication.cc" "BlockChain/src/Dns.cc")

add_executable(${project_name} ${SOURCES})
target_include_directories(${project_name} PRIVATE include)
