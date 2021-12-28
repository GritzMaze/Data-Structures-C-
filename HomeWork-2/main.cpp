#include <iostream>
#include <string>
#include "headers/Tree.h"

using std::string;

int main(int, char**) {
    std::cout << "Hello, world!\n";

    Tree<string> tree("Uspeshnia");
    tree.insert("Gosho", "Uspeshnia");
    tree.insert("Misho", "Uspeshnia");
    tree.insert("Slavi", "Uspeshnia");
    tree.insert("Pesho", "Gosho");
    tree.insert("Dancho", "Gosho");
    tree.insert("Alex", "Pesho");
    tree.insert("Boris", "Dancho");
    tree.insert("Kamen", "Dancho");
    tree.insert("Slav1", "Slavi");
    tree.insert("Slav2", "Slavi");
    tree.insert("Mecho", "Slav1");
    tree.insert("Q12AD1", "Mecho");

    std::cout << tree.findAllDirectChilds("Dancho") << std::endl;
    std::cout << tree.findAllDirectChilds("Uspeshnia") << std::endl;
    std::cout << tree.findAllDirectChilds("Uspesh") << std::endl;
    std::cout << tree.findAllDirectChilds("Slavi") << std::endl;
    std::cout << tree.getHeight() << std::endl;

    tree.print();


    return 0;
}
