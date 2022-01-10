#include <iostream>
#include "hashMap.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";
     HashMap<std::string, int> hash;
    
    hash[ "one"   ] = 1;
    hash[ "two"   ] = 2;
    hash[ "three" ] = 3;
    hash[ "four"  ] = 4;
    hash[ "five"  ] = 5;
    hash[ "six"   ] = 6;
    hash[ "seven" ] = 7;
    hash[ "eight" ] = 8;

    // hash.insert("one", 1);
    // hash.insert("two", 2);
    // hash.insert("three", 3);
    // hash.insert("four", 4);
    // hash.insert("five", 5);
    // hash.insert("six", 6);
    // hash.insert("seven", 7);
    // hash.insert("eight", 8);


    hash.print();
}
