#include "Dns.h"

std::vector<Node> DNS::getNodes() {
    http::Request request(this->address+"api/getNodes");
    const http::Response response = request.send("GET");
    std::string res = std::string(response.body.begin(), response.body.end());
    std::cout << "Complete: " << res << std::endl;
}

void DNS::sendNode() {  }
