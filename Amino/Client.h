#ifndef CLIENT_H
#define CLIENT_H

#include "utils/requester.h"

class Client {
public:
    Client(); 
    void doSomething();
    void doAnotherThing(); 
private:
    Requester requester;

};


#endif //CLIENT_H