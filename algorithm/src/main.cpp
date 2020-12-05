#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <random>

#include "utils.h"


int main() {
    // Make three vectors, each of length 100 filled with 1s, 2s, and 3s
    // std::vector<int> vec1(10, 1);
    // std::vector<int> vec2(10, 2);
    // std::vector<int> vec3(10, 3);
    //
    // // Wrap into a vector
    // std::vector<std::pair<std::string, std::vector<int>>> vals = { {"First", vec1}, {"Second", vec2}, {"Three", vec3} };
    //
    // std::string filepath = "../../data/outinsert/example.csv";
    // Write the vector to CSV
    /*
    write_csv(filepath, vals);
    */

    // read csv
    /*
    std::vector<std::pair<std::string, std::vector<int>>> file = read_csv(filepath);
    for (int i = 0; i < file.size(); i++)
    {
        std::cout << file[i].first << ": ";

        for (auto i : file[i].second)
            std::cout << i << ' ';

        std:cout << endl;
    }
    */

    // test integer number hashing
    std::cout << "Linked Hashing Numbers:\n";
    testNumberLinkedHashMap();
    //test vector of integer number hashing
    std::cout << "Linked Hashing Vectors:\n";
    testVectorLinkedHashMap();

    return 0;
}
