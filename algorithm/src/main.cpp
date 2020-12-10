#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
#include <map>

#include "utils.h"
// #include "LinkedHashMap.h"

#include "CuckooHashMap.h"

std::map<bool, std::string> cresult = {{false, "FAILED" }, { true, "PASSED" }};

bool unitTestCuckooHashMap(bool verbose){
    if (verbose) {
        std::cout << "\n\n*****Unit tets: Cuckoo Hash map *******" << std::endl;
    }
    //test 1
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    CuckooHashMap<int, int> cuckooHmap(2 * (v.size() + 1), v.size());
    for(auto const& value: v){
        cuckooHmap.insert(value, value);
        //cuckooHmap.displayHash();
    }
    bool result = cuckooHmap.insert(11, 11);
    if (verbose) {
        std::cout << "\nTest 1 is " << cresult[result];
        if (!result) {
            cuckooHmap.displayHash();
        }
    }
    if (!result) {

        return false;
    }
    // test 2
    int value;
    result = cuckooHmap.search(3, value);
    result = result && (value == 3);
    if (verbose) {
        std::cout << "\nTest 2 is " << cresult[result];
        if (!result) {
            cuckooHmap.displayHash();
        }
    }
    if (!result) {
        return false;
    }
//
    // test 3
    result = !(cuckooHmap.search(12, value));
    //result = !result && (value != 7);
    if (verbose) {
        std::cout << "\nTest 3 is " << cresult[result];
        if (!result) {
            cuckooHmap.displayHash();
        }
    }
    if (!result) {
        return false;
    }
//
//    // test 4
    bool result1 = cuckooHmap.search(5, value);
    cuckooHmap.remove(5);
    result = result1 && !(cuckooHmap.search(5, value));
    if (verbose) {
        std::cout << "\nTest 4 is " << cresult[result];
        if (!result) {
            cuckooHmap.displayHash();
        }
    }
    if (!result) {
        return false;
    }
    return true;
};

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
//    unitTestLinkedHashMap();
    for (int i = 0; i < 1000; ++i) {
        if (!unitTestCuckooHashMap(true)) {
            std::cout<< "\n" << i << " FAIL\n";
            return 1;
        }
    }
    std::cout<< "\nALL\n";

    // unitTestCuckooHashMap(true);


    // performance evaluation
    //std::cout << "\n\n****Integer Numbers Hashing******";
    //getPerformanceInteger();
    // getPerformanceIntegerLoop();
    // getPerformanceIntegerToFile();
    //
    //
    // std::cout << "\n\n****Integer Vectors Hashing******";
    //std::cout << "\n\n****Strings  Hashing******";
    //getPerformanceString();
    // size_t N = 100;
    // // std::vector<std::string> sample;
    // auto sample = genRandStrings(N);
    // for(auto const& value: sample){
    //     std::cout << value << std::endl;
    //     // hmap.insert(value, value);
    // }


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
