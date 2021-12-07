#pragma once
// #include "Node.h"
#include <stdexcept>
#include "interface.h"

template <class DType>
class PriorityQueue
{
private:
    struct Node
    {
        Node *next = nullptr;
        int priority;
        DType data;
        Node(const DType &data, const int &priority, Node *next = nullptr)
            : data(data), priority(priority), next(next) {}
    };
    Node *front;
    Node *back;

    void clear();

public:
    PriorityQueue();
    ~PriorityQueue();

    bool isEmpty() const;
    void enqueue(const DType &, const int &priority);
    DType dequeue();
    const DType first() const;
};

template <class DType>
PriorityQueue<DType>::PriorityQueue()
{
    front = nullptr;
    back = nullptr;
}

template <class DType>
bool PriorityQueue<DType>::isEmpty() const
{
    return front == nullptr;
}

template <class DType>
void PriorityQueue<DType>::enqueue(const DType &data, const int &priority)
{
    Node *temp = new Node(data, priority);
    Node *it = front;
    if (this->isEmpty())
    {
        this->front = temp;
        this->back = temp;
    }
    else if (front->priority > priority)
    {
        temp->next = front;
        front = temp;
    }
    else
    {
        while (it->next != nullptr && it->next->priority <= priority)
        {
            it = it->next;
        }
        temp->next = it->next;
        it->next = temp;
        if (temp->next == nullptr)
        {
            this->back = temp;
        }
    }
}

template <class DType>
DType PriorityQueue<DType>::dequeue()
{
    Node *temp = this->front;
    DType result = first();
    this->front = this->front->next;

    delete temp;

    return result;
}

template <class DType>
const DType PriorityQueue<DType>::first() const
{
    if (this->isEmpty())
    {
        throw std::underflow_error("Empty queue");
    }
    else
        return this->front->data;
}

template <class DType>
void PriorityQueue<DType>::clear()
{
    while (!this->isEmpty())
    {
        Node *temp = this->front;
        this->front = this->front->next;
        delete temp;
    }
}

template <class DType>
PriorityQueue<DType>::~PriorityQueue()
{
    this->clear();
}