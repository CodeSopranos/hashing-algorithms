#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <random>

#include "utils.h"
// #include "LinkedHashMap.h"

int main() {
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

    // unit tests
    unitTestLinkedHashMap();
    unitTestOpenHashMap();

    // performance evaluation
    std::cout << "\n\n****Integer Numbers Hashing******";
    getPerformanceInteger();
    // getPerformanceIntegerLoop();
    // getPerformanceIntegerToFile();
    //
    //
    // std::cout << "\n\n****Integer Vectors Hashing******";



    //test vector of integer number hashing
    // std::cout << "Hashing Vectors:\n";
    // testVectorLinkedHashMap();
    // std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // std::vector<int> t = {3, 4, 5, 9, 10, 20, 21, 6};
    // const size_t tableSize = 11;
    // HashMap<int, int> hmap(tableSize);
    // // hmap.displayHash();
    // for(auto const& value: v){
    //     // std::cout << value << " ";
    //     hmap.insert(value, value);
    // }
    // hmap.displayHash();
    // int value;
    // for(auto const& key: t){
    //     // std::cout << value << " ";
    //     if(hmap.search(key, value)){
    //       std::cout<<" found " << key <<" "<< value<<std::endl;
    //     }
    //     else{
    //         std::cout<<key<<" not found "<<std::endl;
    // }
    //
    // }
    // for(auto const& value: v){
    //     // std::cout << value << " ";
    //     hmap.remove(value);
    // }
    // hmap.displayHash();


    return 0;
}
