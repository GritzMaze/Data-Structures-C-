#include "../headers/commands.h"

void Commands::start()
{
    std::cout << "Welcome!\n";
    std::cout << "**************************************************************************************\n";
    std::cout << "Type 'help' to see the list of commands.\n";
    std::cout << "Type 'exit' to exit the program.\n";
    std::cout << "Type 'load <filename> <file or path>' to load a hierarchy from a file.\n";
    std::cout << "Type 'save <filename> <file or path>' to save a hierarchy to a file.\n";
    std::cout << "Type 'find <hierarchy> <name>' to find a person in the hierarchy.\n";
    std::cout << "Type 'subordinates <hierarchy> <name>' to find all subordinates of a person in the hierarchy.\n";
    std::cout << "Type 'manager <hierarchy> <name>' to find the manager of a person in the hierarchy.\n";
    std::cout << "Type 'employees <hierarchy>' to find the number of employees in the hierarchy.\n";
    std::cout << "Type 'overloaded <hierarchy>' to find the number of employees with more than 20 subordinates in the hierarchy.\n";
    std::cout << "Type 'join <hierarchy1> <hierarchy2> <name of joined hierarchy>' to join two hierarchies.\n";
    std::cout << "Type 'fire <hierarchy> <name>' to fire a person from the hierarchy.\n";
    std::cout << "Type 'hire <hierarchy> <name> <manager>' to hire a person to a hierarchy.\n";
    std::cout << "Type 'salary <hierarchy> <name>' to find the salary of a person in the hierarchy.\n";
    std::cout << "Type 'incorporate <hierarchy>' to incorporate a hierarchy.\n";
    std::cout << "Type 'modernize <hierarchy>' to modernize a hierarchy.\n";
    std::cout << "**************************************************************************************\n";
    std::cout << "*Note: If you are building with CMake, the default path is 'build/'*\n";
    std::cout << "**************************************************************************************\n";

    string line;
    while (true)
    {
        std::cout << "> ";
        std::cin.clear();
        getline(std::cin, line);
        string command = line.substr(0, line.find(" "));
        transform(command.begin(), command.end(), command.begin(), ::tolower);
        line.erase(0, line.find(" ") + 1);
        if (command == "exit")
        {
            quit();
            break;
        }
        if (command == "help")
        {
            help();
            continue;
        }
        if (command == "load")
        {
            load(line);
            continue;
        }
        if (command == "find")
        {
            find(line);
            continue;
        }
        if (command == "num_subordinates")
        {
            subordinates(line);
            continue;
        }
        if (command == "manager")
        {
            manager(line);
            continue;
        }
        if (command == "num_employees")
        {
            employees(line);
            continue;
        }
        if (command == "overloaded")
        {
            overloaded(line);
            continue;
        }
        if (command == "join")
        {
            join(line);
            continue;
        }
        if (command == "fire")
        {
            fire(line);
            continue;
        }
        if (command == "hire")
        {
            hire(line);
            continue;
        }
        if (command == "salary")
        {
            salary(line);
            continue;
        }
        if (command == "incorporate")
        {
            incorporate(line);
            continue;
        }
        if (command == "modernize")
        {
            modernize(line);
            continue;
        }
        if (command == "save")
        {
            save(line);
            continue;
        }
        std::cout << "Unknown command" << std::endl;
    }
}

void Commands::help()
{
    std::cout << "Welcome!\n";
    std::cout << "**************************************************************************************\n";
    std::cout << "Type 'help' to see the list of commands.\n";
    std::cout << "Type 'exit' to exit the program.\n";
    std::cout << "Type 'load <filename> <file or path>' to load a hierarchy from a file.\n";
    std::cout << "Type 'save <filename> <file or path>' to save a hierarchy to a file.\n";
    std::cout << "Type 'find <hierarchy> <name>' to find a person in the hierarchy.\n";
    std::cout << "Type 'subordinates <hierarchy> <name>' to find all subordinates of a person in the hierarchy.\n";
    std::cout << "Type 'manager <hierarchy> <name>' to find the manager of a person in the hierarchy.\n";
    std::cout << "Type 'employees <hierarchy>' to find the number of employees in the hierarchy.\n";
    std::cout << "Type 'overloaded <hierarchy>' to find the number of employees with more than 20 subordinates in the hierarchy.\n";
    std::cout << "Type 'join <hierarchy1> <hierarchy2> <name of joined hierarchy>' to join two hierarchies.\n";
    std::cout << "Type 'fire <hierarchy> <name>' to fire a person from the hierarchy.\n";
    std::cout << "Type 'hire <hierarchy> <name> <manager>' to hire a person to a hierarchy.\n";
    std::cout << "Type 'salary <hierarchy> <name>' to find the salary of a person in the hierarchy.\n";
    std::cout << "Type 'incorporate <hierarchy>' to incorporate a hierarchy.\n";
    std::cout << "Type 'modernize <hierarchy>' to modernize a hierarchy.\n";
    std::cout << "**************************************************************************************\n";
    std::cout << "*Note: If you are building with CMake, the default path is 'build/'*\n";
    std::cout << "**************************************************************************************\n";
}

void Commands::quit()
{
    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].isModified())
        {
            std::cout << hierarchies[i].getName() << " was modified. Do you want to save it? (y/n)" << std::endl;
            string line;
            std::cout << "> ";
            getline(std::cin, line);
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            if (line == "y")
            {
                string command = hierarchies[i].getName() + " ";
                std::cout << "Enter filename: ";
                getline(std::cin, line);
                command += line;
                save(command);
            }
        }
    }

    std::cout << "Thank you! Bye!" << std::endl;
    exit(0);
}

void Commands::load(string command)
{
    std::cout << "> ";

    string name = command.substr(0, command.find(" "));
    command += " ";
    command.erase(0, command.find(" ") + 1);
    string filename = command;
    if(name == " " || name.empty() || name == "load") {
        std::cout << "Please enter a valid name." << std::endl;
        return;
    }
    std::ifstream file;
    file.open(filename);
    if (file)
    {

        std::stringstream buffer;
        buffer << file.rdbuf();
        string contents = buffer.str();
        Hierarchy h(contents);
        h.setName(name);
        hierarchies.push_back(h);
        std::cout << name << " loaded successfully!" << std::endl;
    }
    else
    {
        if (!filename.empty())
        {
            std::cout << "File not found!" << std::endl;
        }
        std::cout << "Enter hierarchy manually (i.e. Uspeshnia-Gosho):" << std::endl;
        string result;
        std::cout << "> ";
        while (getline(std::cin, command))
        {
            result += command + "\n";
            result.push_back('\n');
            std::cout << "> ";
        }

        Hierarchy h(result);
        h.setName(name);
        h.setModified(true);
        hierarchies.push_back(h);
        std::cout << h.getName() << " loaded successfully!" << std::endl;
    }
}

void Commands::save(string command)
{

    string name = command.substr(0, command.find(" "));
    command += " ";
    command.erase(0, command.find(" ") + 1);
    string filename = command;

    if(name == " " || name.empty() || name == "save") {
        std::cout << "Please enter a valid name." << std::endl;
        return;
    }

    if (filename.empty())
    {
        for (int i = 0; i < hierarchies.size(); i++)
        {
            if (hierarchies[i].getName() == name)
            {
                hierarchies[i].print();
                return;
                break;
            }
        }
        std::cout << name << " was not found." << std::endl;
        return;
    }

    std::ofstream file(filename);

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == name)
        {
            file << hierarchies[i].getString();
            std::cout << "Saved to " << filename << std::endl;
            hierarchies[i].setModified(false);
        }
    }
    file.close();
}

void Commands::find(string command)
{
    string hierarchy = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);
    string name = command;

    std::cout << hierarchies[0].getName() << std::endl;
    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            if (hierarchies[i].find(name))
            {
                std::cout << name << " is employed in " << hierarchy << "." << std::endl;
                return;
            }
            else
            {
                std::cout << name << " does not exist. " << std::endl;
                return;
            }
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}

void Commands::subordinates(string command)
{
    string hierarchy = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);
    string name = command;

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            if (hierarchies[i].find(name))
            {
                std::cout << name << " has " << hierarchies[i].num_subordinates(name) << " subordinates." << std::endl;
                return;
            }
            else
            {
                std::cout << name << " does not exist. " << std::endl;
                return;
            }
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}

void Commands::manager(string command)
{
    string hierarchy = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);
    string name = command;

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            if (hierarchies[i].find(name))
            {
                std::cout << name << " is managed by " << hierarchies[i].manager(name) << "." << std::endl;
                return;
            }
            else
            {
                std::cout << name << " does not exist. " << std::endl;
                return;
            }
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}

void Commands::employees(string command)
{
    string hierarchy = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            std::cout << "There are " << hierarchies[i].num_employees() << " employees in " << hierarchy << "." << std::endl;
            return;
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}

void Commands::overloaded(string command)
{
    string hierarchy = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            std::cout << hierarchy << " has " << hierarchies[i].num_overloaded() << " employees." << std::endl;
            return;
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}

void Commands::join(string command)
{
    string hierarchy1 = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);
    string hierarchy2 = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);
    string resultHierarchy = command;

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy1)
        {
            for (int j = 0; j < hierarchies.size(); j++)
            {
                if (hierarchies[j].getName() == hierarchy2)
                {
                    Hierarchy h = hierarchies[i].join(hierarchies[j]);
                    h.setName(resultHierarchy);
                    h.setModified(true);
                    hierarchies.push_back(h);
                    std::cout << resultHierarchy << " created." << std::endl;
                    return;
                }
            }
            std::cout << hierarchy2 << " does not exist." << std::endl;
            return;
        }
    }
    std::cout << hierarchy1 << " does not exist." << std::endl;
}

void Commands::fire(string command)
{
    string hierarchy = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);
    string name = command;

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            if (hierarchies[i].find(name))
            {
                hierarchies[i].fire(name);
                std::cout << name << " was fired from " << hierarchy << "." << std::endl;
                hierarchies[i].setModified(true);
                return;
            }
            else
            {
                std::cout << name << " does not exist. " << std::endl;
                return;
            }
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}

void Commands::hire(string command)
{
    string hierarchy = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);
    string name = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);
    string manager = command;

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            if (hierarchies[i].hire(name, manager))
            {
                std::cout << name << " was hired in " << hierarchy << " with manager " << manager << "." << std::endl;
                hierarchies[i].setModified(true);
                return;
            }
            else
            {
                std::cout << "Hiring was unsuccessful." << std::endl;
                return;
            }
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}

void Commands::salary(string command)
{
    string hierarchy = command.substr(0, command.find(" "));
    command.erase(0, command.find(" ") + 1);
    string name = command;

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            if (hierarchies[i].find(name))
            {
                std::cout << name << " has salary of " << hierarchies[i].getSalary(name) << " BGN." << std::endl;
                return;
            }
            else
            {
                std::cout << name << " does not exist. " << std::endl;
                return;
            }
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}

void Commands::incorporate(string command)
{
    string hierarchy = command;

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            hierarchies[i].incorporate();
            std::cout << hierarchy << " incorporated." << std::endl;
            hierarchies[i].setModified(true);
            return;
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}

void Commands::modernize(string command)
{
    string hierarchy = command;

    for (int i = 0; i < hierarchies.size(); i++)
    {
        if (hierarchies[i].getName() == hierarchy)
        {
            hierarchies[i].modernize();
            std::cout << hierarchy << " modernized." << std::endl;
            hierarchies[i].setModified(true);
            return;
        }
    }
    std::cout << hierarchy << " does not exist." << std::endl;
}
