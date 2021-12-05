#include <iostream>
#include "queue.h"
#include "myStore.h"

int main(int, char**) {
    Queue<int> temp;
    temp.enqueue(1, 14);
    temp.enqueue(2, 3);
    temp.enqueue(3, 25);

    std::cout << temp.dequeue() << "\n";
    std::cout << temp.dequeue() << "\n";
    std::cout << temp.dequeue() << "\n";

    std::cout << "Hello, world!\n";


    MyStore store;
    Client client1{1,1,1,1};
    Client client2{2,2,2,2};

    store.init(1, 1, 1);
    store.addClients(&client1, 1);
    store.addClients(&client2, 1);

}
