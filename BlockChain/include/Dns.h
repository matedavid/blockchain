#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "HTTPRequest.h"

// Node struct definition
struct Node {
    std::string header;
    std::string online;
    std::string last_connected;
};

// Dns class to communicate with DNS server
class DNS {
private:
    std::string address = "http://127.0.0.1:5000/";
public:
    void sendNode();
    std::vector<Node> getNodes();

    // Send new block to connected nodes
    void sendBlock();
};
