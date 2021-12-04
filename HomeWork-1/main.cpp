#include <iostream>
#include "queue.h"

int main(int, char**) {
    Queue temp;
    temp.enqueue(1);
    temp.enqueue(2);
    temp.enqueue(3);

    std::cout << temp.dequeue() << "\n";
    std::cout << temp.dequeue() << "\n";
    std::cout << temp.dequeue() << "\n";

    std::cout << "Hello, world!\n";
}
