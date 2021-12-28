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
    tree = new Tree(data);
}

Hierarchy::~Hierarchy() noexcept
{
    delete tree;
}

string Hierarchy::print() const
{
    return tree->print();
}

int Hierarchy::longest_chain() const
{
    return tree->getHeight();
}

bool Hierarchy::find(const string &name) const
{
    return tree->find(name);
}

int Hierarchy::num_employees() const
{
    return tree->findAllChilds("Uspeshnia");
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

// ne e gotovo
unsigned long Hierarchy::getSalary(const string &who) const
{
    try
    {
        if (!tree->find(who))
        {
            throw std::invalid_argument("No such employer");
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << '\n';
        return -1;
    }
    int directChilds = tree->findAllDirectChilds(who);
    int notDirectChilds = tree->findAllChilds(who) - directChilds;
    return directChilds * 500 + notDirectChilds * 50;
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

            if (tree->insert(who, boss))
            {
                tree->remove(who);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
}

// ne e gotovo
void Hierarchy::incorporate()
{
    //tree.insert("Uspeshnia", "Uspeshnia");
}

// ne e gotovo
void Hierarchy::modernize()
{
    //tree.insert("Uspeshnia", "Uspeshnia");
}

// ne e gotovo
Hierarchy Hierarchy::join(const Hierarchy &right) const
{
    //tree.insert("Uspeshnia", "Uspeshnia");
    Hierarchy h("Uspeshnia");

    return *this;
}
