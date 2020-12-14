#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <random>

#include "utils.h"
#include "CuckooHashMap.h"

std::map<bool, std::string> cresult = {{false, "FAILED" }, { true, "PASSED" }};

bool unitTestCuckooHashMap(bool verbose) {
    if (verbose) {
        std::cout << "\n\n*****Unit tets: Cuckoo Hash map *******" << std::endl;
    }
    //test 1
    std::vector<int> v = genRandVec(10, 0, 100000);;
    CuckooHashMap<int, int> cuckooHmap(2 * (v.size() + 1), v.size());
    for (auto const &value: v) {
        cuckooHmap.insert(value, value);
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

bool unitTestCuckooHashMapStrings(bool verbose, int testVecSize, int baseVecSize){
    if (verbose) {
        std::cout << "\n\n*****Unit tets: Cuckoo Hash map *******" << std::endl;
    }
    //test 1
    std::vector<std::string> v1 = genRandStrings(baseVecSize);
    std::vector<std::string> v = genRandStrings(testVecSize);

    CuckooHashMap<std::string, std::string> cuckooHmap(2 * (v.size() + v1.size()),
                                                       10);
    for (auto const &value: v1) {
        cuckooHmap.insert(value, value);
        //cuckooHmap.displayHash();
    }
//    for (auto const &value: v) {
//        cuckooHmap.insert(value, value);
//        //cuckooHmap.displayHash();
//    }
//    bool result = cuckooHmap.insert("100001", "100001");
//    if (verbose) {
//        std::cout << "\nTest 1 is " << cresult[result];
//        if (!result) {
//            //cuckooHmap.displayHash();
//
//        }
//    }
//    if (!result) {
//        std::cout << "[";
//        for (auto const &value: v) {
//            std::cout << value << ", ";
//        }
//        std::cout << "]" << std::endl;
//        return false;
//    }
//    // test 2
//    std::string value;
//    for (auto const &v_: v) {
//        result = cuckooHmap.search(v_, value);
//        result = result && (value == v_);
//        if (verbose) {
//            std::cout << "\nTest 2 is " << cresult[result];
//            if (!result) {
//                //cuckooHmap.displayHash();
//            }
//        }
//    }
//    if (!result) {
//        std::cout << "[";
//        for (auto const &value: v) {
//            std::cout << value << ", ";
//        }
//        std::cout << "]" << std::endl;
//        return false;
//    }
////
//    std::string value_;
//    // test 3
//    result = !(cuckooHmap.search("100002", value_));
//    //result = !result && (value != 100002);
//    if (verbose) {
//        std::cout << "\nTest 3 is " << cresult[result];
//        if (!result) {
//            //cuckooHmap.displayHash();
//        }
//    }
//    if (!result) {
//        std::cout << "[";
//        for (auto const &value: v) {
//            std::cout << value << ", ";
//        }
//        std::cout << "]" << std::endl;
//        return false;
//    }
////
////    // test 4
//    bool result1 = cuckooHmap.search(v[0], value);
//    cuckooHmap.remove(v[0]);
//    result = result1 && !(cuckooHmap.search(v[0], value));
//    if (verbose) {
//        std::cout << "\nTest 4 is " << cresult[result];
//        if (!result) {
//            //cuckooHmap.displayHash();
//        }
//    }
//    if (!result) {
//        std::cout << "[";
//        for (auto const &value: v) {
//            std::cout << value << ", ";
//        }
//        std::cout << "]" << std::endl;
//        return false;
//    }
    return true;
};

void stressTestCuckooHashMap() {

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const size_t tableSize = 9;
    size_t stressSize = 5000;
    int value;
    bool result, result1, result2;

    std::cout << "\n\n**Stress test: Cuckoo Hash map**"<< std::endl;
    for (auto i=0; i < stressSize; ++i){
        // test 1
        CuckooHashMap<int, int> cuckooHmap(tableSize, v.size());
        for (auto const &value : v) {
            cuckooHmap.insert(value, value);
        }
        result = cuckooHmap.insert(11, 11);
        if (!result){
            cuckooHmap.displayHash();
            std::cout << "[";
            for (auto const &value: v) {
                std::cout << value << ", ";
            }
            std::cout << "]" << std::endl;
            std::cout<<"TEST 1 is FAILED (itr: "<<i << " )"<<std::endl;
            break;
        }
        // test 2
        value = 0;
        CuckooHashMap<int, int> cuckooHmap1(tableSize, v.size());
        for (auto const &value : v) {
            cuckooHmap1.insert(value, value);
        }
        result = cuckooHmap1.search(3, value);
        result = result && (value == 3);
        if (!result){
            std::cout<<"TEST 2 is FAILED (itr: "<<i << " )"<<std::endl;
            break;
        }
        // test 3
        value = 0;
        CuckooHashMap<int, int> cuckooHmap2(tableSize, v.size());
        for (auto const &value : v) {
            //cuckooHmap2.displayHash();
            cuckooHmap2.insert(value, value);
        }
        result = cuckooHmap2.search(7, value);
        result = result && (value == 7);
        if (!result){
            cuckooHmap2.displayHash();
            std::cout << "[";
            for (auto const &value: v) {
                std::cout << value << ", ";
            }
            std::cout << "]" << std::endl;
            std::cout<<"TEST 3 is FAILED (itr: "<<i << " )"<<std::endl;
            break;
        }
        // test 4
        value = 0;
        CuckooHashMap<int, int> cuckooHmap3(tableSize, v.size());
        for (auto const &value : v) {
            //cuckooHmap3.displayHash();
            cuckooHmap3.insert(value, value);
        }
        result1 = cuckooHmap3.search(5, value);
        cuckooHmap3.remove(5);
        result = result1 && !(cuckooHmap3.search(5, value));
        if (!result){
            std::cout<<"TEST 4 is FAILED (itr: "<<i << " )"<<std::endl;
            break;
        }
    }
};


