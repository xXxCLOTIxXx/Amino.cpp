#include "Client.h"

#include <iostream>

Client::Client() {
}

void Client::doSomething() {
}

void Client::doAnotherThing() {
    std::cout << requester.sendRequest("GET", "/g/s/search/amino-id-and-link?q=fnaf") << std::endl;
}