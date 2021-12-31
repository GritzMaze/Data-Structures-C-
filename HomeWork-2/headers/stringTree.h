
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
    Node *findSubtree(const string &, Node *);
    bool remove(const string &, Node *&);
    bool removeLink(const string&, Node*&);

    int height(const Node *) const;
    int findAllChilds(const Node *);
    int findAllDirectChilds(const Node *);
    int findMoreThanNthChilds(const int&, const Node*);
    string findParent(const string &, Node *);
    bool reasign(const string&, const string&, Node*&, Node*&);
    bool insert(const string &, const string &, Node *&);
    string printByLevels(const Node *) const;
    string printAllOnLevel(const int &, string, const Node *) const;
    int getLevel(const string&, Node*) const;
    void sortChilds(Node*);
    void incorporate(Node*);
    void makeBoss(const string&, Node*);
    void modernize(int , Node*);
    Tree join(const Node*, const Node*, const Tree*, const Tree*) const;

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

    int findAllChilds(const string &);
    int findAllDirectChilds(const string &);
    int findMoreThanNthChilds(const int&);
    int getHeight() const;
    int getSize() const;
    int getLevel(const string &) const;
    Node* getRoot() const;
    string getParent(const string &);
    bool isEmpty() const;
    string findParent(const string&);
    bool reasign(const string&, const string&);
    void incorporate();
    unsigned long getSalary(const string&);
    void modernize();
    Tree join(const Tree*) const;

    bool insert(const string &, const string &);
    string print() const;
    string print2() const;
    string print2(const Node*) const;
};
