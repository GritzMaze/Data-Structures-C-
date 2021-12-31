#include <iostream>
#include <string>
#include "interface.h"

using std::string;

int main(int, char**) {
    std::cout << "Hello, world!\n";

    // Hierarchy h("Uspeshnia");
    // h.hire("Gosho", "Uspeshnia");
    // h.hire("Misho", "Uspeshnia");
    // h.hire("Slavi", "Uspeshnia");
    // h.hire("Pesho", "Gosho");
    // h.hire("Dancho", "Gosho");
    // h.hire("Alex", "Pesho");
    // h.hire("Boris", "Dancho");
    // h.hire("Kamen", "Dancho");
    // h.hire("Slav1", "Slavi");
    // h.hire("Slav2", "Slavi");
    // h.hire("Mecho", "Slav1");
    // h.hire("Q12AD1", "Mecho");

    // std::cout << h.getSalary("Uspeshnia") << std::endl;
    // std::cout << h.getSalary("Q12AD1") << std::endl;
    // std::cout << h.getSalary("Mecho") << std::endl;
    // std::cout << h.getSalary("Mech") << std::endl;
    // string result = h.print();
    // std::cout << std::endl;

    // std::cout << h.manager("Misho") <<std::endl;
    // std::cout << h.manager("Mecho") <<std::endl;
    // std::cout << h.manager("Mec") <<std::endl;

    // std::cout << h.num_overloaded(1) <<std::endl;
    // std::cout << h.num_overloaded(2) <<std::endl;
    // std::cout << h.num_overloaded(3) <<std::endl;


    // std::cout << h.hire("Dancho", "Slav1") << std::endl;
    // std::cout << h.hire("Dancho", "Uspeshn") << std::endl;

    // h.print();

    // Hierarchy h2("");
    // string h5 = h2.print();
    // std::cout << h2.num_employees() << std::endl;
    const string TheBoss = "Uspeshnia";

const string lozenec =
    "Uspeshnia - Gosho \n"
    "Uspeshnia - Misho \n"
    "Gosho     - Pesho \n"
    "Gosho     - Dancho\n"
    "Pesho     - Alex  \n"
    "Dancho    - Boris \n"
    "Dancho    - Kamen \n"
    "Uspeshnia - Slavi \n"
    "Slavi     - Slav1 \n"
    "Slavi     - Slav2 \n"
    "Slav1     - Mecho \n"
    "Mecho     - Q12Adl\n";

const string large =
    "Uspeshnia - 1\n"
    "1-2\n1-3\n1-4\n1-5\n1-6\n1-7\n"
    "2-21\n2-22\n2-23\n2-24\n2-25\n2-26\n2-27\n2-28\n"
    "3-31\n3-32\n3-33\n3-34\n3-35\n3-36\n3-37\n3-38\n3-39\n";

const string loz_new =
    " Uspeshnia   -  MishoPetrov \n"
    " MishoPetrov -  Misho       \n"
    " MishoPetrov -  Slav        \n";

    // Hierarchy h(loz_new);
    // Hierarchy h2(large);
    Hierarchy h3(lozenec);

    string str1 = "Dancho";
    string str2 = "Pesho";
     //h3.modernize();
    h3.hire("Slav1", "Dancho");
    h3.print();

    return 0;
}
