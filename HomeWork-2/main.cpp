#include <iostream>
#include <string>
#include "interface.h"

using std::string;

int main(int, char**) {
    std::cout << "Hello, world!\n";

    Hierarchy h("Uspeshnia");
    h.hire("Gosho", "Uspeshnia");
    h.hire("Misho", "Uspeshnia");
    h.hire("Slavi", "Uspeshnia");
    h.hire("Pesho", "Gosho");
    h.hire("Dancho", "Gosho");
    h.hire("Alex", "Pesho");
    h.hire("Boris", "Dancho");
    h.hire("Kamen", "Dancho");
    h.hire("Slav1", "Slavi");
    h.hire("Slav2", "Slavi");
    h.hire("Mecho", "Slav1");
    h.hire("Q12AD1", "Mecho");

    std::cout << h.getSalary("Uspeshnia") << std::endl;
    std::cout << h.getSalary("Q12AD1") << std::endl;
    std::cout << h.getSalary("Mecho") << std::endl;
    std::cout << h.getSalary("Mech") << std::endl;
    string result = h.print();
    std::cout << std::endl;
    std::cout << result;

    return 0;
}
