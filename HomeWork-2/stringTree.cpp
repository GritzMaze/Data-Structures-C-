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
    Node *newNode = new Node(other->data, copy(other->child), copy(other->siblings));
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

Node *Tree::findSubtree(const string &data, Node *node) const
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

int Tree::height(const Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return std::max(1 + height(node->child), height(node->siblings));
}

int Tree::findAllChilds(const Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + findAllChilds(node->child) + findAllChilds(node->siblings);
}

int Tree::findAllDirectChilds(const Node *node) const
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
            root->child = new Node(data);
            size++;
            return true;
        }
        else
        {
            Node *child = root->child;
            while (child->siblings != nullptr)
            {
                child = child->siblings;
            }
            child->siblings = new Node(data);
        }
    }
    else
    {
        return insert(data, name, root->child) || insert(data, name, root->siblings);
    }
    return false;
}

//
// void Tree::printByLevels(const Node* root) const
// {
//     if (root == nullptr)
//     {
//         return;
//     }
//     else
//     {
//         while (root)
//         {
//             std::cout << " " << root->data;
//             if (root->child)
//                 printByLevels(root->child); // First, if child exists, traverse child.
//             root = root->siblings;  // Next, traverse sibling
//         }
//     }
// }

string Tree::printByLevels(const Node *root) const
{
    string result = "";
    if (!root)
        return result;
    std::queue<const Node *> front;
    front.push(root);
    front.push(nullptr);
    for (;;)
    {
        const Node *current = front.front();
        front.pop();
        if (!current)
        {
            std::cout << '\n';
            result.push_back('\n');
            if (front.empty())
                return result;
            front.push(nullptr);
        }
        else
        {
            result.append(current->data);
            result.append(" ");
            std::cout << current->data << ' ';
            for (const Node *it = current->child; it; it = it->siblings)
            {
                front.push(it);
            }
        }
    }
    return result;
}

string Tree::print() const
{
    return printByLevels(root);
}

int Tree::findAllChilds(const string &name) const
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
    int result = findAllChilds(temp) - 1;
    return (result < 0 ? 0 : result);
}

int Tree::findAllDirectChilds(const string &name) const
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
    int result = findAllDirectChilds(temp->child);
    return (result < 0 ? 0 : result);
}
