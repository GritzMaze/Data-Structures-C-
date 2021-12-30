#include "headers/stringTree.h"

Tree::Tree(const Tree &other)
{
    root = copy(other.root);
    size = other.size;
}

Tree::Tree(Tree &&other)
{
    root = other.root;
    size = other.size;
    other.root = nullptr;
    other.size = 0;
}

Tree::Tree(const string &data)
{
    root = new Node(data);
    size = 1;
}

Tree::~Tree()
{
    clear(root);
}

Tree &Tree::operator=(const Tree &other)
{
    if (this != &other)
    {
        clear(root);
        root = copy(other.root);
        size = other.size;
    }
    return *this;
}

Tree &Tree::operator=(Tree &&other)
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

bool Tree::find(const string &data) const
{
    return find(data, root);
}

bool Tree::remove(const string &data)
{
    return remove(data, root);
}

int Tree::getHeight() const
{
    return height(root);
}

int Tree::getSize() const
{
    return size;
}

bool Tree::isEmpty() const
{
    return size == 0;
}

Node *Tree::copy(Node *other)
{
    if (other == nullptr)
    {
        return nullptr;
    }
    Node *newNode = new Node(other->data, other->parent, copy(other->child), copy(other->siblings));
    return newNode;
}

void Tree::clear(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    clear(node->child);
    clear(node->siblings);
    delete node;
}

bool Tree::find(const string &data, Node *node) const
{
    if (node == nullptr || data.empty())
    {
        return false;
    }
    if (node->data == data)
    {
        return true;
    }
    return find(data, node->child) || find(data, node->siblings);
}

Node *Tree::findSubtree(const string &data, Node *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->data == data)
    {
        return node;
    }
    Node *result = findSubtree(data, node->child);
    if (result == nullptr)
    {
        result = findSubtree(data, node->siblings);
    }
    return result;
}

bool Tree::remove(const string &data, Node *&root)
{
    if (root == nullptr)
    {
        return false;
    }

    // If data is found
    if (root->data == data)
    {
        Node *temp = root;
        // If root has no children
        if (root->child == nullptr)
        {
            root = root->siblings;
        }
        else
        { // If root has children
            Node *child = root->child;
            string par = root->parent;
            while (child->siblings != nullptr)
            { // Find the last child
                child = child->siblings;
            }
            child->siblings = root->siblings; // Set the last child's sibling to root's sibling
            root = root->child;               // Up a level
            delete temp;
            Node *temp = root;
            while (temp->siblings != nullptr)
            {
                temp->parent = par;
                temp = temp->siblings;
            }
            Node *parent = findSubtree(par, this->root);
            sortChilds(parent);
        }
        size--;
        return true;
    }
    return remove(data, root->child) || remove(data, root->siblings);
}

bool Tree::removeLink(const string &data, Node *&root)
{
    if (root == nullptr)
    {
        return false;
    }

    // If data is found
    if (root->child->data == data)
    {
        root->child = root->child->siblings;
        return true;
    }
    else
    {
        Node *child = root->child;
        while (child->siblings != nullptr)
        {
            if (child->siblings->data == data)
            {
                child->siblings = child->siblings->siblings;
                return true;
            }
            child = child->siblings;
        }
    }
    return remove(data, root->child) || remove(data, root->siblings);
}

int Tree::height(const Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return std::max(1 + height(node->child), height(node->siblings));
}

int Tree::findAllChilds(const Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + findAllChilds(node->child) + findAllChilds(node->siblings);
}

int Tree::findAllDirectChilds(const Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + findAllDirectChilds(node->siblings);
}

bool Tree::insert(const string &data, const string &name)
{
    return insert(data, name, root);
}

bool Tree::insert(const string &data, const string &name, Node *&root)
{
    if (root == nullptr)
    {
        return false;
    }

    if (root->data == name)
    {
        if (root->child == nullptr)
        {
            root->child = new Node(data, root->data);
            size++;
            return true;
        }
        else
        {
            Node *child = root->child;
            string temp = root->data;
            bool flag = false;
            if (data < child->data)
            {
                root->child = new Node(data, temp, nullptr, root->child);
                flag = true;
            }
            else
            {
                while (child->siblings != nullptr)
                {
                    if (data < child->siblings->data)
                    {
                        child->siblings = new Node(data, temp, nullptr, child->siblings);
                        flag = true;
                        break;
                    }
                    child = child->siblings;
                }
            }
            size++;
            if (!flag)
                child->siblings = new Node(data, temp);
            return true;
        }
    }
    else
    {
        return insert(data, name, root->child) || insert(data, name, root->siblings);
    }
    return false;
}

bool Tree::reasign(const string &data, const string &name)
{
    Node *subTree = findSubtree(data, root);
    return reasign(data, name, subTree, root);
}

bool Tree::reasign(const string &data, const string &name, Node *&subTree, Node *&root)
{
    if (root == nullptr)
    {
        return false;
    }
    Node *parent = findSubtree(subTree->parent, this->root);

    if (root->data == name)
    {
        if (root->child == nullptr)
        {
            root->child = subTree;
            removeLink(data, parent);
            subTree->parent = root->data;
            sortChilds(root);
            return true;
        }
        else
        {
            Node *child = root->child;
            while (child->siblings != nullptr)
            {
                child = child->siblings;
            }
            child->siblings = subTree;
            removeLink(data, parent);
            subTree->parent = root->data;
            sortChilds(root);
            return true;
        }
    }
    else
    {
        return reasign(data, name, subTree, root->child) || reasign(data, name, subTree, root->siblings);
    }
    return false;
}

string Tree::printByLevels(const Node *root) const
{
    string result = "";
    if (!root)
        return result;

    int height = getHeight();
    for (int i = 2; i <= height; i++)
    {
        result.append(printAllOnLevel(i, "", root));
    }
    std::cout << result;
    return result;
}

string Tree::printAllOnLevel(const int &level, string result, const Node *root) const
{
    if (!root)
        return "";
    if (getLevel(root->data) == level)
    {
        result.append(root->parent);
        result.push_back('-');
        result.append(root->data);
        result.push_back('\n');
        result.append(printAllOnLevel(level, "", root->siblings));
        return result;
    }
    else
    {
        result.append(printAllOnLevel(level, "", root->child));
        return result + printAllOnLevel(level, "", root->siblings);
    }

    return result;
}

string Tree::print() const
{
    return printByLevels(root);
}

int Tree::findAllChilds(const string &name)
{
    Node *temp = findSubtree(name, root);
    try
    {
        if (!temp)
            throw std::invalid_argument("No such name");
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
        return 0;
    }
    int result = findAllChilds(temp->child);
    return (result < 0 ? 0 : result);
}

int Tree::findAllDirectChilds(const string &name)
{
    Node *temp = findSubtree(name, root);
    try
    {
        if (!temp)
            throw std::invalid_argument("No such name");
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
        return -1;
    }
    int result = findAllDirectChilds(temp->child);
    return (result < 0 ? 0 : result);
}

string Tree::findParent(const string &name)
{
    return findParent(name, root);
}

string Tree::findParent(const string &name, Node *node)
{
    Node *temp = findSubtree(name, root);

    try
    {
        if (!temp)
            throw std::invalid_argument("No such name");
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
        return "";
    }
    string result = temp->parent;
    return result;
}

int Tree::findMoreThanNthChilds(const int &n)
{

    return findMoreThanNthChilds(n, root);
}

int Tree::findMoreThanNthChilds(const int &n, const Node *root)
{
    if (root == nullptr)
        return 0;

    if (findAllChilds(root->child) > n)
    {
        return 1 + findMoreThanNthChilds(n, root->child) + findMoreThanNthChilds(n, root->siblings);
    }
    else
        return findMoreThanNthChilds(n, root->child) + findMoreThanNthChilds(n, root->siblings);
}

int Tree::getLevel(const string &name) const
{
    return getLevel(name, root);
}

int Tree::getLevel(const string &name, Node *node) const
{
    if (node == nullptr)
        return 0;
    if (node->data == name)
        return 1;
    int result = getLevel(name, node->child);
    if (result != 0)
        return result + 1;
    return getLevel(name, node->siblings);
}

void Tree::sortChilds(Node *&root)
{
    if (root == nullptr)
        return;

    bool flag = true;

    Node *child = root->child;
    Node *temp;

    if(child->siblings == nullptr)
        return;

    if (child->data > child->siblings->data)
    {
        temp = child->siblings;
        child->siblings = child;
        child = temp;
        flag = false;
    }
    else {
    while (child->siblings != nullptr)
    {
        if (child->data > child->siblings->data)
        {

            flag = false;
            child = child->siblings;
            break;
        }
        child = child->siblings;
    }
    }
    if (flag)
        return;
    sortChilds(root);
}

void Tree::incorporate()
{
    incorporate(root->child);
}

void Tree::incorporate(Node *root)
{
    if (root == nullptr)
        return;
    incorporate(root->child);
    incorporate(root->siblings);
     Node *toPromote = root;
     Node *child = root;
    if(!child->siblings) return;
    while (child->siblings != nullptr)
    {

        if (getSalary(toPromote->data) < getSalary(child->data))
        {
            toPromote = child->siblings;
        }
        child = child->siblings;
    }
    makeBoss(toPromote->data, findSubtree(toPromote->parent, this->root));
}

unsigned long Tree::getSalary(const string &name)
{
    try
    {
        if (!find(name))
        {
            throw std::invalid_argument("No such employer");
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
        return -1;
    }
    int directChilds = findAllDirectChilds(name);
    int notDirectChilds = findAllChilds(name) - directChilds;
    return directChilds * 500 + notDirectChilds * 50;
}

void Tree::makeBoss(const string &name, Node *root)
{
    string parent;
    // if its left child
    if(root->child->data == name) {
        root->child->child = root->child->siblings;
        root->siblings = nullptr;
        
        if(root->child->child)
        {
            Node* child = root->child->child;
            parent = child->parent;
            while(child->siblings)
            {
                child->parent = parent;
                child = child->siblings;
            }
        }
        return;
    }


    // if it is in the right siblings
    Node *child = root->child;
    Node *child_f = root->child;
    while(child->siblings != nullptr) {
        if(child->siblings->data == name) { // if the next child is the needed one
            child->siblings->child = child_f;  // Making it the parrent
            parent = child->siblings->data; // Saving the parent
            child->siblings = child->siblings->siblings; // Setting the current child to the +1 child 
            child->siblings->siblings = nullptr; //Setting the now parent's siblings to nullptr
            break;
        }
        child = child->siblings;
    }

    Node* child_i = child_f;
    while(child_i->siblings != nullptr) {
        child_i->parent = parent;
        child_i = child_i->siblings;
    }
    return;
}

void Tree::modernize() {
    modernize(0, root);
}

void Tree::modernize(int level, Node *root) {
    if(root == nullptr) return;
    modernize(level + 1, root->child);
    modernize(level + 1, root->siblings);
    if(root->child != nullptr && level % 2 == 0) {
        remove(root->child->data);
    }
}