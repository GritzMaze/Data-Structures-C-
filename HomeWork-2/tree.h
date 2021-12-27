#pragma once
#include <iostream>
#include <string>
#include <queue>

using std::string;

template <class DataType>
struct Node
{
    DataType data;
    Node *child;
    Node *siblings;
    Node(const DataType &data, Node *child = nullptr, Node *siblings = nullptr)
        : data(data), child(child), siblings(siblings) {}
};

template <class DataType>
class Tree
{
private:
    Node<DataType> *root;
    int size;

    Node<DataType> *copy(Node<DataType> *);
    void clear(Node<DataType> *);

    bool find(const DataType &, Node<DataType> *) const;
    bool remove(const DataType &, Node<DataType> *&);

    int height(const Node<DataType> *) const;
    bool insert(const DataType &, const string &, Node<DataType> *&);

public:
    Tree() : root(nullptr), size(0) {}
    Tree(const Tree &);
    Tree(Tree &&);
    ~Tree();
    Tree &operator=(const Tree &);
    Tree &operator=(Tree &&);

    bool find(const DataType &) const;
    bool remove(const DataType &);

    int getHeight() const;
    int getSize() const;
    bool isEmpty() const;

    void insert(const DataType &, const string &);
    void printByLevels(const Node<DataType>*) const;
};