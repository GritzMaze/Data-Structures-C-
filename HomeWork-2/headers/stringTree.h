
#pragma once
#include <iostream>
#include <string>
#include <queue>

using std::string;

struct Node
{
    string data;
    Node *child;
    Node *siblings;
    string parent;
    Node(const string &data, string parent = "", Node *child = nullptr, Node *siblings = nullptr)
        : data(data), child(child), siblings(siblings), parent(parent) {}
};

class Tree
{
private:
    Node *root;
    int size;

    Node *copy(Node *);
    void clear(Node *);

    bool find(const string &, Node *) const;
    Node *findSubtree(const string &, Node *) const;
    bool remove(const string &, Node *&);
    bool removeLink(const string&, Node*&);

    int height(const Node *) const;
    int findAllChilds(const Node *) const;
    int findAllDirectChilds(const Node *) const;
    int findMoreThanNthChilds(const int&, const Node*) const;
    string findParent(const string &, Node *) const;
    bool reasign(const string&, const string&, Node*&, Node*&);
    bool insert(const string &, const string &, Node *&);
    string printByLevels(const Node *) const;

public:
    Tree() : root(nullptr), size(0) {}
    Tree(const Tree &);
    Tree(Tree &&);
    Tree(const string &);
    ~Tree();
    Tree &operator=(const Tree &);
    Tree &operator=(Tree &&);

    bool find(const string &) const;
    bool remove(const string &);

    int findAllChilds(const string &) const;
    int findAllDirectChilds(const string &) const;
    int findMoreThanNthChilds(const int&) const;
    int getHeight() const;
    int getSize() const;
    int getLevel(const string &) const;
    bool isEmpty() const;
    string findParent(const string&) const;
    bool reasign(const string&, const string&);

    bool insert(const string &, const string &);
    string print() const;
};
