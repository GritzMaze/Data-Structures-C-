#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "hashMap.h"
#include "interface.h"

int main(int argc, char **argv)
{
  

    // if (argc != 3)
    //     throw std::invalid_argument("More or less than 2 arguments");

    // std::string file1 = argv[1];
    // std::string file2 = argv[2];
    std::string file1 = "C:\\Users\\Sprint\\github\\Data-Structures-C++\\HomeWork-3\\big_data1.txt";
    std::string file2 = "C:\\Users\\Sprint\\github\\Data-Structures-C++\\HomeWork-3\\big_data2.txt";

    // start timer
    auto start = std::chrono::high_resolution_clock::now();

    std::stringstream file1_stream;
    std::stringstream file2_stream;
    
    std::ifstream file_s1;
    file_s1.open(file1);
    if (file_s1)
    {

        file1_stream << file_s1.rdbuf();
        file_s1.close();
    }
    else
    {
        std::cout << "File 1 not found!" << std::endl;
        std::cout << "Ending program..." << std::endl;
        file_s1.close();
        return 0;
    }

    std::ifstream file_s2;
    file_s2.open(file2);
    if (file_s2)
    {

        file2_stream << file_s2.rdbuf();
        file_s2.close();
    }
    else
    {
        std::cout << "File 2 not found!" << std::endl;
        std::cout << "Ending program..." << std::endl;
        file_s2.close();
        return 0;
    }

    Comparator c;
    ComparisonReport report = c.compare(file1_stream, file2_stream);
    c.compareInPercentage(report);
    // end timer
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    // print timer
    std::cout << "Time: " << diff.count() << " s" << std::endl;
    return 0;
}
