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
    return 0;
}
