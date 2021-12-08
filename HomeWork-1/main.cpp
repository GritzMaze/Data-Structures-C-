#include <iostream>
#include <vector>
#include "headers/myClient.h"
#include "headers/myStore.h"


int main(int, char**) {

int workers, numClients;
int min, bananas, schweppes, maxTime;

std::vector<Client> clients;

std::cin >> workers >> numClients;

while(numClients--) {
    std::cin >> min >> bananas >> schweppes >> maxTime;
    clients.push_back(Client{min, bananas, schweppes, maxTime});
}


    MyStore store;
    store.init(workers, 0, 0);
    store.addClients(clients.data(), clients.size());
    store.advance();
    
    // Client client1{0, 300, 0, 10};
    // Client client2{5, 300, 0, 10};
    
    // MyStore store;
    // store.init(5, 0, 0);
    // store.addClients(&client1, 1);
    // store.addClients(&client2, 1);

    // store.advanceTo(15);
    return 0;
}
