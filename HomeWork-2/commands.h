#pragma once
#include <iostream>
#include "interface.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

class Commands {
    public:
        void start();

    private:

        vector<Hierarchy> hierarchies;

        void help();
        void quit();
        void load(string command);
        void find(string command);
        void subordinates(string command);
        void manager(string command);
        void employees(string command);
        void overloaded(string command);
        void join(string command);
        void fire(string command);
        void hire(string command);
        void salary(string command);
        void incorporate(string command);
        void modernize(string command);
        void save(string command);

};