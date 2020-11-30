#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

#include "utils.h"

#include "HashNode.h"
#include "KeyHash.h"
#include "HashMap.h"

const size_t tableSize = 5;

struct MyKeyHash {
    unsigned long operator()(const int& key) const
    {
        return key % tableSize;
    }
};


int main() {
    // Make three vectors, each of length 100 filled with 1s, 2s, and 3s
    std::vector<int> vec1(10, 1);
    std::vector<int> vec2(10, 2);
    std::vector<int> vec3(10, 3);

    // Wrap into a vector
    std::vector<std::pair<std::string, std::vector<int>>> vals = { {"First", vec1}, {"Second", vec2}, {"Three", vec3} };

    std::string filepath = "../../data/output/example.csv";
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

    //test simple hash map
    HashMap <int, std::string, tableSize, MyKeyHash> hmap;

    hmap.put(1, "val1");
    hmap.put(2, "val2");
    hmap.put(6, "val3");
    hmap.put(7, "val4");

    std::string value;
    hmap.get(6, value);
    std::cout << value << std::endl;
    bool res = hmap.get(3, value);
    if (res)
        std::cout << value << std::endl;
  /*  hmap.remove(3);
    res = hmap.get(3, value);
    if (res)
        cout << value << endl;*/
    std::vector<int> rand_vec(20);
    rand_vec = gen_rand_vec(20);
    for(auto const& value: rand_vec)
        std::cout << value << " " << std::endl;
    return 0;
}
