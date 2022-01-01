#include "headers/stringTree.h"

Tree::Tree(const Tree &other)
{
    root = copy(other.root);
    size = other.size;
}

Tree::Tree(const Tree *other)
{
    root = copy(other->root);
    size = other->size;
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

Node *Tree::getSubtree(const string &data)
{
    return findSubtree(data, root);
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
        // If root has no children
        if (root->child == nullptr)
        {
            Node *temp = root;
            root = root->siblings;
            delete temp;
        }
        else
        { // If root has children
            Node *child = root->child;
            string par = root->parent;
            child->parent = par;
            while (child->siblings != nullptr)
            { // Find the last child
                child->siblings->parent = par;
                child = child->siblings;
            }
            child->siblings = root->siblings; // Set the last child's sibling to root's sibling
            root = root->child;               // Up a level
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
        Node *temp = root->child;
        root->child = root->child->siblings;
        temp->siblings = nullptr;
        return true;
    }
    else
    {
        Node *child = root->child;
        while (child->siblings != nullptr)
        {
            if (child->siblings->data == data)
            {
                Node *temp = child->siblings;
                child->siblings = child->siblings->siblings;
                temp->siblings = nullptr;
                return true;
            }
            child = child->siblings;
        }
    }
    return removeLink(data, root->child) || removeLink(data, root->siblings);
}

bool Tree::rename(const string &data, const string &newName, Node *root)
{
    if (root == nullptr)
    {
        return false;
    }

    // If data is found
    if (root->data == data)
    {
        // If root has no children
        if (root->child == nullptr)
        {
            root->data = newName;
        }
        else
        { // If root has children
            Node *child = root->child;
            string par = root->parent;
            child->parent = newName;
            while (child->siblings != nullptr)
            { // Find the last child
                child->siblings->parent = par;
                child = child->siblings;
            }
            root->data = newName;
        }
        return true;
    }
    return rename(data, newName, root->child) || rename(data, newName, root->siblings);
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

    if (root->data == name)
    {
        Node *parent = findSubtree(subTree->parent, this->root);
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

string Tree::toString() const
{
    string result = "";
    if (!root)
        return result;

    int height = getHeight();
    for (int i = 2; i <= height; i++)
    {
        result.append(printAllOnLevel(i, "", root));
    }
    return result;
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

void Tree::sortChilds(Node *root)
{
    if (root == nullptr)
        return;

    bool flag = true;

    Node *child = root->child;
    Node *temp;

    if (child->siblings == nullptr)
        return;

    if (child->data > child->siblings->data)
    {
        temp = child->siblings;
        child->siblings = child->siblings->siblings;
        temp->siblings = child;
        root->child = temp;
        flag = false;
    }
    else
    {
        Node *prev = nullptr;
        while (child->siblings != nullptr)
        {
            if (child->data > child->siblings->data)
            {

                flag = false;
                // Swap nodes
                prev->siblings = child->siblings;
                child->siblings = child->siblings->siblings;
                prev->siblings->siblings = child;
                break;
            }
            prev = child;
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
    if (!child->siblings)
        return;

    if (root->data != findSubtree(findParent(root->data), this->root)->child->data)
        return;

    while (child->siblings != nullptr)
    {

        if (getSalary(toPromote->data) < getSalary(child->siblings->data))
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
    if (root->child->data == name)
    {

        parent = root->child->data;
        if (root->child->child)
        {
            root->child->child->siblings = root->child->siblings;
            root->child->siblings = nullptr;
            if (root->child->child->siblings)
                sortChilds(root->child);
        }
        else
        {
            root->child->child = root->child->siblings;
            root->child->child->parent = root->child->data;
            root->child->siblings = nullptr;
        }
        Node *child = root->child->child;
        while (child)
        {
            child->parent = parent;
            child = child->siblings;
        }
        return;
    }

    // if it is in the right siblings
    Node *child = root->child;
    while (child->siblings)
    {
        if (child->siblings->data == name)
        { // if the next child is the needed one
            Node *temp = child->siblings;
            parent = temp->data;                         // Saving the parent
            child->siblings = child->siblings->siblings; // swap
            root->child = temp;                          // swap
            temp->siblings = nullptr;                    //Setting the now parent's siblings to nullptr
            root->child->child->siblings = child;        // swap

            break;
        }
        child = child->siblings;
    }

    Node *child_i = root->child->child;
    while (child_i)
    {
        child_i->parent = parent;
        child_i = child_i->siblings;
    }
    if (root->child->child->siblings)
        sortChilds(root->child);
    return;
}

void Tree::modernize()
{
    modernize(0, root);
}

void Tree::modernize(int level, Node *root)
{
    if (root == nullptr)
        return;
    modernize(level + 1, root->child);
    modernize(level, root->siblings);
    if (root->child != nullptr && level % 2 != 0 && root->data != "Uspeshnia")
    {
        remove(root->data);
    }
}

string Tree::print2() const
{
    return print2(root);
}

string Tree::print2(const Node *root) const
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

string Tree::join(Tree *tree)
{
    Tree *result = new Tree(tree);
    if (!tree->getRoot() || !root)
        return "";
    result->join(result->getRoot()->child, root->child, result, this);
    if (!result)
        return "";
    string stringResult = result->toString();
    delete result;
    return stringResult;
}

// Join two trees
void Tree::join(const Node *f_root, const Node *s_root, Tree *f_tree, Tree *s_tree)
{
    if (!f_root || !s_root || !this->root)
        return;

    const Node *current_employee = s_root;
    if (current_employee->data != "Uspeshnia")
    {
        if (find(current_employee->data))
        {
            string f_parent = f_tree->findParent(current_employee->data);

            Node *subtree = f_tree->findSubtree(current_employee->data, f_tree->root);
            try
            {
                if (find(current_employee->parent, subtree))
                {
                    throw std::logic_error("Invalid entry! Parent is a child in the other tree!");
                }
            }
            catch (std::logic_error &e)
            {
                this->~Tree();
                this->root = nullptr;
                std::cout << e.what() << '\n';
                return;
            }
            if (current_employee->parent != f_parent)
            {

                int level_s_tree = s_tree->getLevel(current_employee->parent);
                int level_f_tree = f_tree->getLevel(f_parent);
                if (level_f_tree > level_s_tree)
                {
                    this->insert(current_employee->data + "toRename", current_employee->parent);
                    this->reasign(current_employee->data, current_employee->data + "toRename");
                    this->remove(current_employee->data);
                    this->rename(current_employee->data + "toRename", current_employee->data, this->root);
                }
                else if (level_f_tree == level_s_tree)
                {
                    if (current_employee->parent < f_parent)
                    {
                        this->insert(current_employee->data + "toRename", current_employee->parent);
                        this->reasign(current_employee->data, current_employee->data + "toRename");
                        this->remove(current_employee->data);
                        this->rename(current_employee->data + "toRename", current_employee->data, this->root);
                    }
                }
            }
        }
        else
        {
            this->insert(current_employee->data, current_employee->parent);
        }
    }

    this->join(f_root, s_root->child, f_tree, s_tree);
    this->join(f_root, s_root->siblings, f_tree, s_tree);

    return;
}

string Tree::getParent(const string &name)
{
    return findParent(name, root);
}

Node *Tree::getRoot() const
{
    return root;
}