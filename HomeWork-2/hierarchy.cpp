#include "interface.h"

Hierarchy::Hierarchy(Hierarchy &&r) noexcept
{
    tree = r.tree;
    r.tree = nullptr;
}

Hierarchy::Hierarchy(const Hierarchy &r)
{
    tree = new Tree(*r.tree);
}

Hierarchy::Hierarchy(const string &data)
{
    if (data.empty())
    {
        tree = new Tree("");
        return;
    }
    tree = new Tree("Uspeshnia");
    std::stringstream ss(data);
    string line;
    while (getline(ss, line))
    {
        if (line.empty())
            continue;

        if (!(countWords(line) > 0 && countWords(line) <= 3 && countDel(line, '-') == 1))
        {
            throw std::invalid_argument("Invalid input");
        }

        line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char x)
                                  { return std::isspace(x); }),
                   line.end());
        std::replace(line.begin(), line.end(), '-', ' ');
        std::stringstream line_s(line);
        string name;
        string boss;
        line_s >> boss >> name;
        if (!tree->find(boss))
        {
            throw std::invalid_argument("No such boss");
        }
        tree->insert(name, boss);
    }
}

Hierarchy::~Hierarchy() noexcept
{
    delete tree;
    tree = nullptr;
}

string Hierarchy::print() const
{
    return tree->print();
}

int Hierarchy::longest_chain() const
{
    if (tree->getSize() == 1)
    {
        return 0;
    }
    return tree->getHeight();
}

bool Hierarchy::find(const string &name) const
{
    return tree->find(name);
}

int Hierarchy::num_employees() const
{
    if (find("Uspeshnia"))
        return tree->getSize();

    return 0;
}

int Hierarchy::num_overloaded(int level) const
{
    return tree->findMoreThanNthChilds(level);
}

string Hierarchy::manager(const string &name) const
{
    return tree->findParent(name);
}

int Hierarchy::num_subordinates(const string &name) const
{
    return tree->findAllDirectChilds(name);
}

unsigned long Hierarchy::getSalary(const string &who) const
{
    return tree->getSalary(who);
}

bool Hierarchy::fire(const string &who)
{
    try
    {
        if (who == "Uspeshnia")
        {
            throw std::invalid_argument("You can't fire the bossman!");
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
        return false;
    }
    return tree->remove(who);
}

bool Hierarchy::hire(const string &who, const string &boss)
{
    if (!find(who))
    {
        return tree->insert(who, boss);
    }
    else
    {
        if (tree->findAllChilds(who) == 0)
        {
            tree->remove(who);
            return tree->insert(who, boss);
        }
        else
        {
            return tree->reasign(who, boss);
        }
    }
    return false;
}

void Hierarchy::incorporate()
{
    return tree->incorporate();
}


void Hierarchy::modernize()
{
    tree->modernize();
}

Hierarchy Hierarchy::join(const Hierarchy &right) const
{
    string Tree = tree->join(right.getTree());
    if (Tree.empty())
    {
        return Hierarchy("");
    }
    else return Hierarchy(Tree);
}

int Hierarchy::getLevel(const string &name) const
{
    return tree->getLevel(name);
}

unsigned Hierarchy::countWords(const string &str) const
{
    if (str.empty())
        return 0;

    bool inSpaces = true;
    unsigned count = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (isspace(str[i]))
        {
            inSpaces = true;
        }
        else if (inSpaces)
        {
            inSpaces = false;
            count++;
        }
    }
    return count;
}

unsigned Hierarchy::countDel(const string &str, char ch) const
{
    if (str.empty())
        return 0;

    unsigned count = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ch)
        {
            count++;
        }
    }
    return count;
}

Tree *Hierarchy::getTree() const
{
    return tree;
}