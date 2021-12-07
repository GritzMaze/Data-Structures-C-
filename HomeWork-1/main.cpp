#include <iostream>
#include "headers/priorityQueue.h"
#include "headers/myStore.h"

int main(int, char**) {
    //  PriorityQueue<int> temp;
    //  temp.enqueue(1, 14);
    //  temp.enqueue(2, 3);
    //  temp.enqueue(3, 25);
    //  temp.enqueue(4, 25);
    //  temp.enqueue(5, 26);

    //  std::cout << temp.dequeue() << "\n";
    //  std::cout << temp.dequeue() << "\n";
    //  std::cout << temp.dequeue() << "\n";
    //  std::cout << temp.dequeue() << "\n";
    //  std::cout << temp.dequeue() << "\n";

    // MyStore store;
    // store.init(1, 100, 0);
    // Client client1{0, 100, 0, 1};
    // Client client2{10, 1, 0, 1};
    // store.addClients(&client1, 1);
    // store.addClients(&client2, 1);
    // store.advanceTo(9);
    // store.advanceTo(10);



    // LAST TEST CASE

    // MyStore store;
    // store.init(2, 10, 0);
    // Client client1{0, 10, 10, 20};
    // Client client2{10, 10, 0, 0};
    // store.addClients(&client1, 1);
    // store.addClients(&client2, 1);
    // store.advanceTo(0);
    // store.advanceTo(10);
    // store.advanceTo(20);


    MyStore store;
    Client client1{0,10,0 ,10};
    Client client2{45,35,0,30};
    Client client3{46,30,20,100};
    Client client4{200,10,10,1};

    store.init(5, 0, 0);
    store.addClients(&client1, 1);
    store.addClients(&client2, 1);
    store.addClients(&client3, 1);
    store.addClients(&client4, 1);
    store.advanceTo(1000);
    return 0;
}
