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
// #include "ChainedHashMap.h"
#include "OpenedHashMap.h"

#include "CuckooHashMap.h"

std::map<bool, std::string> cresult = {{false, "FAILED" }, { true, "PASSED" }};

using namespace std;
using namespace std::chrono;

bool unitTestCuckooHashMap(bool verbose) {
    if (verbose) {
        std::cout << "\n\n*****Unit tets: Cuckoo Hash map *******" << std::endl;
    }
    //test 1
    std::vector<int> v = genRandVec(10, 0, 100000);;
    CuckooHashMap<int, int> cuckooHmap(2 * (v.size() + 1), v.size());
    for (auto const &value: v) {
        cuckooHmap.insert(value, value);
        cuckooHmap.displayHash();
    }
    bool result = cuckooHmap.insert(100001, 100001);
    if (verbose) {
        std::cout << "\nTest 1 is " << cresult[result];
        if (!result) {
            cuckooHmap.displayHash();

        }
    }
    if (!result) {
        std::cout << "[";
        for (auto const &value: v) {
            std::cout << value << ", ";
        }
        std::cout << "]" << std::endl;
        return false;
    }
    // test 2
    int value;
    for (auto const &v_: v) {
        result = cuckooHmap.search(v_, value);
        result = result && (value == v_);
        if (verbose) {
            std::cout << "\nTest 2 is " << cresult[result];
            if (!result) {
                cuckooHmap.displayHash();
            }
        }
    }
    if (!result) {
        std::cout << "[";
        for (auto const &value: v) {
            std::cout << value << ", ";
        }
        std::cout << "]" << std::endl;
        return false;
    }
//
    int value_;
    // test 3
    result = !(cuckooHmap.search(100002, value_));
    //result = !result && (value != 100002);
    if (verbose) {
        std::cout << "\nTest 3 is " << cresult[result];
        if (!result) {
            cuckooHmap.displayHash();
        }
    }
    if (!result) {
        std::cout << "[";
        for (auto const &value: v) {
            std::cout << value << ", ";
        }
        std::cout << "]" << std::endl;
        return false;
    }
//
//    // test 4
    bool result1 = cuckooHmap.search(v[0], value);
    cuckooHmap.remove(v[0]);
    result = result1 && !(cuckooHmap.search(v[0], value));
    if (verbose) {
        std::cout << "\nTest 4 is " << cresult[result];
        if (!result) {
            cuckooHmap.displayHash();
        }
    }
    if (!result) {
        std::cout << "[";
        for (auto const &value: v) {
            std::cout << value << ", ";
        }
        std::cout << "]" << std::endl;
        return false;
    }
    return true;
};

bool unitTestCuckooHashMapStrings(bool verbose){
    if (verbose) {
        std::cout << "\n\n*****Unit tets: Cuckoo Hash map strings *******" << std::endl;
    }
    //test 1
    std::vector<std::string> v = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    CuckooHashMap<std::string, std::string> cuckooHmap(2 * (v.size() + 1), v.size());
    for(auto const& value: v){
        cuckooHmap.insert(value, value);
        cuckooHmap.displayHash();
    }
    bool result = cuckooHmap.insert("11", "11");
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
    std::string value;
    result = cuckooHmap.search("3", value);
    result = result && (value == "3");
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
    std::string value_;
    // test 3
    result = !(cuckooHmap.search("12", value_));
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
    bool result1 = cuckooHmap.search("5", value);
    cuckooHmap.remove("5");
    result = result1 && !(cuckooHmap.search("5", value));
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
  std::vector<std::pair<std::string, std::vector<int>>> file =
  read_csv(filepath); for (int i = 0; i < file.size(); i++)
  {
      std::cout << file[i].first << ": ";

      for (auto i : file[i].second)
          std::cout << i << ' ';

      std:cout << endl;
  }
  */

  // unit tests
    //unitTestChainedHashMap();
    //unitTestOpenHashMap();

    // unit tests
//    unitTestLinkedHashMap();
    // for (int i = 0; i < 1000; ++i) {
    //     if (!unitTestCuckooHashMap(true)) {
    //         std::cout<< "\n" << i << " FAIL\n";
    //         return 1;
    //     }
    // }
    // std::cout<< "\nALL\n";
    //unitTestCuckooHashMap(true);
    //unitTestCuckooHashMapStrings(true);
    //int value;
    //size_t testSize = 100, vecSize = 2000;
    //vector<int> baseVec, testVec;
    //baseVec = genRandVec(vecSize, 0, 100000);
    //testVec = genRandVec(testSize, 0, 100000);
////
    //CuckooHashMap<int, int> cuckooHmap(2*(vecSize + testSize), vecSize + testSize);
    //for (auto const &value : baseVec) {
    //    cuckooHmap.insert(value, value);
    //}
    //// test inserts
    //auto start = high_resolution_clock::now();
    //for (auto const &value : testVec) {
    //    cuckooHmap.insert(value, value);
    //}
    //auto stop = high_resolution_clock::now();
    //float duration = duration_cast<microseconds>(stop - start).count();
    //int ins = cuckooHmap.getNumberOfInserts();
    //cout << "Average insert time: " << duration / ins << " microsec" << endl;
    //// test search
    //start = high_resolution_clock::now();
    //for (auto const &key : testVec) {
    //    cuckooHmap.search(key, value);
    //}
    //stop = high_resolution_clock::now();
    //duration = duration_cast<microseconds>(stop - start).count();
    //cout << "Average search time: " << duration / testSize << " microsec" << endl;
//
    // test delete
    // start = high_resolution_clock::now();
    // for (auto const &key : testVec) {
    //     cuckooHmap.remove(key);
    // }
    // stop = high_resolution_clock::now();
    // duration = duration_cast<microseconds>(stop - start).count();
    // cout << "Average delete time: " << duration / testSize << " microsec" << endl;
    // performance evaluation
    //std::cout << "\n\n****Integer Numbers Hashing******";
    getPerformanceInteger();
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

    // performance evaluation
  //std::cout << "\n\n****Integer Numbers Hashing******";
  //getPerformanceInteger();
  // getPerformanceIntegerLoop();
  // getPerformanceIntegerToFile();

  //std::cout << "\n\n****Strings  Hashing******";
  //getPerformanceString();

  // size_t N = 100;
  // // std::vector<std::string> sample;
  // auto sample = genRandStrings(N);
  // for(auto const& value: sample){
  //     std::cout << value << std::endl;
  //     // hmap.insert(value, value);
  // }

  // std::cout << "\n\nUnit test OPEN hash \n\n";
  // std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // std::vector<int> t = {3, 4, 5, 9, 10, 20, 21, 6};
  // size_t tableSize = 9;
  //
  // OpenHashMap<int, int> hmap(tableSize, "LINEAR");
  // hmap.displayHash();
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
  // for(auto const& value: t){
  //     // std::cout << value << " ";
  //     hmap.remove(value);
  // }
  // hmap.displayHash();
  //
  // for(auto const& value: v){
  //     // std::cout << value << " ";
  //     hmap.remove(value);
  // }
  // hmap.displayHash();
  //
  // for(auto const& value: v){
  //     // std::cout << value << " ";
  //     hmap.insert(value, value);
  // }
  // hmap.displayHash();

  // std::cout << "\n\nUnit test OPEN hash STRING \n\n";
  // std::vector<std::string> vs = {"111", "244", "1", "99412", "aavsa", "a",
  // "vdasr", "hello", "1sa11rf4f5", "end" }; std::vector<std::string> ts =
  // {"244", "1", "99412", "aavsa", "a", "vdasr", "NO", "ALSO NO"}; size_t
  // tableSize = 9;
  //
  // OpenHashMap<std::string, std::string> shmap(tableSize, "LINEAR");
  // shmap.displayHash();
  // for(auto const& value: vs){
  //     // std::cout << value << " ";
  //     shmap.insert(value, value);
  // }
  // shmap.displayHash();
  // std::string svalue;
  // for(auto const& key: ts){
  //     // std::cout << value << " ";
  //     if(shmap.search(key, svalue)){
  //       std::cout<<" found " << key <<" "<< svalue<<std::endl;
  //     }
  //     else{
  //         std::cout<<key<<" not found "<<std::endl;
  // }
  //
  // }
  // for(auto const& value: ts){
  //     // std::cout << value << " ";
  //     shmap.remove(value);
  // }
  // shmap.displayHash();
  //
  // for(auto const& value: vs){
  //     // std::cout << value << " ";
  //     shmap.remove(value);
  // }
  // shmap.displayHash();
  //
  // for(auto const& value: vs){
  //     // std::cout << value << " ";
  //     shmap.insert(value, value);
  // }
  // shmap.displayHash();

  return 0;
}
