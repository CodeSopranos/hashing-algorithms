#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <random>
#include <map>
#include <vector>
#include <chrono>

#include "utils.h"

using namespace std;
using namespace std::chrono;


int main() {
    //getPerformanceInteger();
//
    //// stress tests
    //stressTestChainedHashMap();
    //stressTestOpenHashMap();
    //stressTestCuckooHashMap();

    for (int i = 0; i < 10; ++i) {
        std::cout<< "\n" << i << " OK\n";
        if (!unitTestCuckooHashMapStrings(true, 100, 100)) {
            std::cout<< "\n" << i << " FAIL\n";
            return 1;
        }
    }

    //// performance evaluation
    //std::cout << "\n\n****Integer Numbers Hashing****";
    //getPerformanceIntegerToFile();
    std::cout << "\n\n****Strings  Hashing****";
    //getPerformanceStringToFile();
    std::cout<<"SUCK ASS\n";
//
    //// real life data
    //std::cout << "\n\n***Real life data hashing***\n";
    //realLifeDataTets();

    //std::cout<< "\nALL\n";
    return 0;
}
