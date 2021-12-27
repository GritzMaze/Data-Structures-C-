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
    bool insert(const DataType &, const DataType &, Node<DataType> *&);
    void printByLevels(const Node<DataType> *) const;

public:
    Tree() : root(nullptr), size(0) {}
    Tree(const Tree &);
    Tree(Tree &&);
    Tree(const DataType &);
    ~Tree();
    Tree &operator=(const Tree &);
    Tree &operator=(Tree &&);

    bool find(const DataType &) const;
    bool remove(const DataType &);

    int getHeight() const;
    int getSize() const;
    bool isEmpty() const;

    bool insert(const DataType &, const DataType &);
    void print() const;
};

template <class DataType>
Tree<DataType>::Tree(const Tree &other)
{
    root = copy(other.root);
    size = other.size;
}

template <class DataType>
Tree<DataType>::Tree(Tree &&other)
{
    root = other.root;
    size = other.size;
    other.root = nullptr;
    other.size = 0;
}

template <class DataType>
Tree<DataType>::Tree(const DataType &data)
{
    root = new Node<DataType>(data);
    size = 1;
}

template <class DataType>
Tree<DataType>::~Tree()
{
    clear(root);
}

template <class DataType>
Tree<DataType> &Tree<DataType>::operator=(const Tree &other)
{
    if (this != &other)
    {
        clear(root);
        root = copy(other.root);
        size = other.size;
    }
    return *this;
}

template <class DataType>
Tree<DataType> &Tree<DataType>::operator=(Tree &&other)
{
    if (this != &other)
    {
        clear(root);
        root = other.root;
        size = other.size;
        other.root = nullptr;
        other.size = 0;
    }
    return *this;
}

template <class DataType>
bool Tree<DataType>::find(const DataType &data) const
{
    return find(data, root);
}

template <class DataType>
bool Tree<DataType>::remove(const DataType &data)
{
    return remove(data, root);
}

template <class DataType>
int Tree<DataType>::getHeight() const
{
    return height(root);
}

template <class DataType>
int Tree<DataType>::getSize() const
{
    return size;
}

template <class DataType>
bool Tree<DataType>::isEmpty() const
{
    return size == 0;
}

template <class DataType>
Node<DataType> *Tree<DataType>::copy(Node<DataType> *other)
{
    if (other == nullptr)
    {
        return nullptr;
    }
    Node<DataType> *newNode = new Node<DataType>(other->data, copy(other->child), copy(other->siblings));
    return newNode;
}

template <class DataType>
void Tree<DataType>::clear(Node<DataType> *node)
{
    if (node == nullptr)
    {
        return;
    }
    clear(node->child);
    clear(node->siblings);
    delete node;
}

template <class DataType>
bool Tree<DataType>::find(const DataType &data, Node<DataType> *node) const
{
    if (node == nullptr)
    {
        return false;
    }
    if (node->data == data)
    {
        return true;
    }
    return find(data, node->child) || find(data, node->siblings);
}

template <class DataType>
bool Tree<DataType>::remove(const DataType &data, Node<DataType> *&root)
{
    if (root == nullptr)
    {
        return false;
    }

    // If data is found
    if (root->data == data)
    {
        Node<DataType> *temp = root;
        // If root has no children
        if (root->child == nullptr)
        {
            root = root->siblings;
        }
        else
        { // If root has children
            Node<DataType> *child = root->child;
            while (child->siblings != nullptr)
            { // Find the last child
                child = child->siblings;
            }
            child->siblings = root->siblings; // Set the last child's sibling to root's sibling
            root = root->child;               // Up a level
        }
        delete temp;
        size--;
        return true;
    }
    return remove(data, root->child) || remove(data, root->siblings);
}

template <class DataType>
int Tree<DataType>::height(const Node<DataType> *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return std::max(1 + height(node->child), height(node->siblings));
}

template <class DataType>
bool Tree<DataType>::insert(const DataType &data, const DataType &name)
{
    return insert(data, name, root);
}

template <class DataType>
bool Tree<DataType>::insert(const DataType &data, const DataType &name, Node<DataType> *&root)
{
    if (root == nullptr)
    {
        return false;
    }

    if (root->data == name)
    {
        if (root->child == nullptr)
        {
            root->child = new Node<DataType>(data);
            size++;
            return true;
        }
        else
        {
            Node<DataType> *child = root->child;
            while (child->siblings != nullptr)
            {
                child = child->siblings;
            }
            child->siblings = new Node<DataType>(data);
        }
    }
    else
    {
        return insert(data, name, root->child) || insert(data, name, root->siblings);
    }
    return false;
}

template <class DataType>
void Tree<DataType>::printByLevels(const Node<DataType>* root) const
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        while (root)
        {
            std::cout << " " << root->data;
            if (root->child)
                printByLevels(root->child); // First, if child exists, traverse child. No return statement following here.
            root = root->siblings;  // Next, traverse sibling
        }
    }
}

template <class DataType>
void Tree<DataType>::print() const
{
    printByLevels(root);
}
