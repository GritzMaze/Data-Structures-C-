#pragma once
// #include "Node.h"
#include <stdexcept>

class Queue
{
private:
    struct Node
    {
        Node *next = nullptr;
        int data;
        Node(const int& data, Node* next = nullptr) : data(data), next(next) {}
    };
    Node *front;
    Node *back;

    void clear();

public:
    Queue();
    ~Queue();

    bool isEmpty() const;
    void enqueue(const int &);
    int dequeue();
    const int first() const;
};

Queue::Queue()
{
    front = nullptr;
    back = nullptr;
}

bool Queue::isEmpty() const
{
    return front == nullptr;
}

void Queue::enqueue(const int &num)
{
    Node* temp = new Node(num);
    if(this->isEmpty()) {
        this->front = temp;
    }
    else {
        this->back->next = temp;
    }
    this->back = temp;
}

int Queue::dequeue() {
    Node* temp = this->front;
    int result = first();
    this->front = this->front->next;

    delete temp;
    
    return result;
}

const int Queue::first() const {
    if(this->isEmpty()) {
       throw std::underflow_error("Empty queue"); 
    }
    else return this->front->data;
}

void Queue::clear() {
    while(!this->isEmpty()) {
        Node* temp = this->front;
        this->front = this->front->next;
        delete temp;
    }
}

Queue::~Queue() {
    this->clear();
}