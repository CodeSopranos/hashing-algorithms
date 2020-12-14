#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1

#include <chrono>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

// standart maps
#include <hash_map>
#include <map>

// our implementation
#include "ChainedHashMap.h"
#include "CuckooHashMap.h"
#include "OpenedHashMap.h"
#include "utils.h"
#include "auxPerformance.h"


using namespace std;
using namespace std::chrono;



void getPerformanceInteger() {
  const size_t tableSize = 10000;

  size_t testSize, vecSize = 5000;
  // cout << "\nEnter baseSize: ";
  // cin >> vecSize;
  cout << "\nEnter testSize: ";
  cin >> testSize;

  vector<int> baseVec, testVec;
  baseVec = genRandVec(vecSize, 0, 100000);
  testVec = genRandVec(testSize, 0, 100000);

  /*      std::map part            */
  cout << "\n*******STD::MAP*************" << endl;
  std::map<int, int> stdMap;
  for (auto const &value : baseVec) {
    // cout << "[" << value << "]" << endl;
    stdMap.insert(std::make_pair(value, value));
  }
  // test inserts
  auto start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    stdMap.insert(std::make_pair(value, value));
  }
  auto stop = high_resolution_clock::now();
  float duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;

  // test search
  std::map<int, int>::iterator it;
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    it = stdMap.find(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    stdMap.erase(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;

  /*      std::map part            */
  cout << "\n*******STD::HASH_MAP*************" << endl;
  std::hash_map<int, int> stdHashMap;
  for (auto const &value : baseVec) {
    // cout << "[" << value << "]" << endl;
    stdHashMap.insert(std::make_pair(value, value));
  }
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    stdHashMap.insert(std::make_pair(value, value));
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;

  // test search
  std::hash_map<int, int>::iterator hit;
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    hit = stdHashMap.find(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    stdHashMap.erase(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;

  /*      Chained Hash Map part            */
  cout << "\n****Chained Hash map*******" << endl;
  HashMap<int, int> hmap(tableSize);
  for (auto const &value : baseVec) {
    // cout << "[" << value << "]" << endl;
    hmap.insert(value, value);
  }
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    hmap.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  int value;
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    hmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    hmap.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;

  /*      Opened Hash Map part          */
  cout << "\n*****Opened Hash map __LINEAR__*******" << endl;
  OpenHashMap<int, int> openHmapL(tableSize, "LINEAR");
  for (auto const &value : baseVec) {
    openHmapL.insert(value, value);
  }
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    openHmapL.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapL.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapL.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;

  cout << "\n*****Opened Hash map __QUADRATIC__*******" << endl;
  OpenHashMap<int, int> openHmapLQdr(tableSize, "QUADRATIC");
  for (auto const &value : baseVec) {
    openHmapLQdr.insert(value, value);
  }
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    openHmapLQdr.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapLQdr.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapLQdr.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;

  cout << "\n*****Opened Hash map __DOUBLE__*******" << endl;
  OpenHashMap<int, int> openHmapLDbl(tableSize, "DOUBLE");
  for (auto const &value : baseVec) {
    openHmapLDbl.insert(value, value);
  }
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    openHmapLDbl.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapLDbl.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapLDbl.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;

  /*      CoCoo Hash Map part          */
    cout << "\n*****OCoCoo Hash Map *******" << endl;
    CuckooHashMap<int, int> cuckooHmap(2*(vecSize + testSize), vecSize + testSize);
    for (auto const &value : baseVec) {
        cuckooHmap.insert(value, value);
    }
    // test inserts
    start = high_resolution_clock::now();
    for (auto const &value : testVec) {
        cuckooHmap.insert(value, value);
    }
    //cuckooHmap.resetCounters();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    cout << "Average insert time: " << duration / cuckooHmap.getNumberOfInserts() << " microsec" << endl;
    // test search
    start = high_resolution_clock::now();
    for (auto const &key : testVec) {
        cuckooHmap.search(key, value);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    cout << "Average search time: " << duration / testSize << " microsec" << endl;
    // test delete
    start = high_resolution_clock::now();
    for (auto const &key : testVec) {
        cuckooHmap.remove(key);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    cout << "Average delete time: " << duration / testSize << " microsec" << endl;

};



void getPerformanceIntegerToFile()
{
  size_t tableSize;
  size_t testSize, vecSize;
  vector<int> baseVec, testVec;
  string filepath = "../data/output/integerPerformanceM2N_1.csv";
  vector<string> HashTableSize, DataSize;

  vector<string> insertMap, insertHashMap;
  vector<string> searchMap, searchHashMap;
  vector<string> deleteMap, deleteHashMap;

  vector<string> attemptsChained, attemptsOpened_linear, attemptsOpened_quadratic, attemptsOpened_double, attemptsCocoo;

  vector<string> insertChained, insertOpened_linear, insertOpened_quadratic, insertOpened_double, insertCocoo;
  vector<string> searchChained, searchOpened_linear, searchOpened_quadratic, searchOpened_double, searchCocoo;
  vector<string> deleteChained, deleteOpened_linear, deleteOpened_quadratic, deleteOpened_double, deleteCocoo;

  typedef HashMap <int, int> intChainedHashMap;
  typedef OpenHashMap <int, int> intOpenedHashMap;
  typedef CuckooHashMap <int, int> intCuckooHashMap;

  cout << "\n\nProgress: ";
  for (auto i=1; i<=ITERATIONS; ++i){
    if (i % 10 == 0){
      cout<<"#";
    }
    tableSize = 100 * i;
    vecSize = tableSize / COEFFICIENT;
    testSize = OPERATIONS;
    baseVec = genRandVec(vecSize, 0, 100000);
    testVec = genRandVec(testSize, 0, 100000);

    HashTableSize.push_back(to_string(tableSize));
    DataSize.push_back(to_string(vecSize));

    /*      std::map part            */
    //std::map<int, int> stdMap;
    //for (auto const &value : baseVec) {
    //  stdMap.insert(std::make_pair(value, value));
    //}
    //// test inserts
    //auto start = high_resolution_clock::now();
    //for (auto const &value : testVec) {
    //  stdMap.insert(std::make_pair(value, value));
    //}
    //auto stop = high_resolution_clock::now();
    //float duration = duration_cast<microseconds>(stop - start).count();
    //insertMap.push_back(to_string(duration / testSize));
    //// test search
    //std::map<int, int>::iterator it;
    //start = high_resolution_clock::now();
    //for (auto const &key : testVec) {
    //  it = stdMap.find(key);
    //}
    //stop = high_resolution_clock::now();
    //duration = duration_cast<microseconds>(stop - start).count();
    //searchMap.push_back(to_string(duration / testSize));
    //// test delete
    //start = high_resolution_clock::now();
    //for (auto const &key : testVec) {
    //  stdMap.erase(key);
    //}
    //stop = high_resolution_clock::now();
    //duration = duration_cast<microseconds>(stop - start).count();
    //deleteMap.push_back(to_string(duration / testSize));
//
    ///*      std::hash_map part            */
    //std::hash_map<int, int> stdHashMap;
    //for (auto const &value : baseVec) {
    //  // cout << "[" << value << "]" << endl;
    //  stdHashMap.insert(std::make_pair(value, value));
    //}
    //// test inserts
    //start = high_resolution_clock::now();
    //for (auto const &value : testVec) {
    //  stdHashMap.insert(std::make_pair(value, value));
    //}
    //stop = high_resolution_clock::now();
    //duration = duration_cast<microseconds>(stop - start).count();
    //insertHashMap.push_back(to_string(duration / testSize));
    //// test search
    //std::hash_map<int, int>::iterator hit;
    //start = high_resolution_clock::now();
    //for (auto const &key : testVec) {
    //  hit = stdHashMap.find(key);
    //}
    //stop = high_resolution_clock::now();
    //duration = duration_cast<microseconds>(stop - start).count();
    //searchHashMap.push_back(to_string(duration / testSize));
    //// test delete
    //start = high_resolution_clock::now();
    //for (auto const &key : testVec) {
    //  stdHashMap.erase(key);
    //}
    //stop = high_resolution_clock::now();
    //duration = duration_cast<microseconds>(stop - start).count();
    //deleteHashMap.push_back(to_string(duration / testSize));

    intCuckooHashMap cuckooHMap(tableSize, vecSize + testSize);
    for(auto const& value: baseVec){
        cuckooHMap.insert(value, value);
    }
    auxPerformanceFunc<intCuckooHashMap, int>(cuckooHMap, testVec, insertCocoo, searchCocoo, deleteCocoo, attemptsCocoo);

    //intChainedHashMap hmap(tableSize);
    //for(auto const& value: baseVec){
    //    hmap.insert(value, value);
    //}
    //auxPerformanceFunc<intChainedHashMap, int>(hmap, testVec, insertChained, searchChained, deleteChained, attemptsChained);
//
    //intOpenedHashMap openedHmapL(tableSize, "LINEAR");
    //for(auto const& value: baseVec){
    //    openedHmapL.insert(value, value);
    //}
    //auxPerformanceFunc<intOpenedHashMap, int>(openedHmapL, testVec, insertOpened_linear, searchOpened_linear, deleteOpened_linear, attemptsOpened_linear);
//
    //intOpenedHashMap openedHmapQ(tableSize, "QUADRATIC");
    //for(auto const& value: baseVec){
    //    openedHmapQ.insert(value, value);
    //}
    //auxPerformanceFunc<intOpenedHashMap, int>(openedHmapQ, testVec, insertOpened_quadratic, searchOpened_quadratic, deleteOpened_quadratic, attemptsOpened_quadratic);
//
    //intOpenedHashMap openedHmapD(tableSize, "DOUBLE");
    //for(auto const& value: baseVec){
    //    openedHmapD.insert(value, value);
    //}
    //auxPerformanceFunc<intOpenedHashMap, int>(openedHmapD, testVec, insertOpened_double, searchOpened_double, deleteOpened_double, attemptsOpened_double);
  }
//    vector<pair<string, vector<string>>> vals = {   {"TableSize", HashTableSize},
//                                                    {"DataSize", DataSize},
//
//                                                    {"insertStdMap",
//                                                    insertMap},
//                                                    {"searchStdMap",
//                                                    searchMap},
//                                                    {"deleteStdMap",
//                                                    deleteMap},
//
//                                                    {"insertStdHashMap",
//                                                    insertHashMap},
//                                                    {"searchStdHashMap",
//                                                    searchHashMap},
//                                                    {"deleteStdHashMap",
//                                                    deleteHashMap},
//
//                                                    {"insertChained",
//                                                    insertChained},
//                                                    {"searchChained",
//                                                    searchChained},
//                                                    {"deleteChained",
//                                                    deleteChained},
//                                                    {"attemptsChained",
//                                                    attemptsChained},
//
//                                                    {"insertOpened_linear",
//                                                    insertOpened_linear},
//                                                    {"searchOpened_linear",
//                                                    searchOpened_linear},
//                                                    {"deleteOpened_linear",
//                                                    deleteOpened_linear},
//                                                    {"attemptsOpened_linear",
//                                                      attemptsOpened_linear},
//
//                                                    {"insertOpened_quadratic",
//                                                    insertOpened_quadratic},
//                                                    {"searchOpened_quadratic",
//                                                    searchOpened_quadratic},
//                                                    {"deleteOpened_quadratic",
//                                                    deleteOpened_quadratic},
//                                                    {"attemptsOpened_quadratic",
//                                                    attemptsOpened_quadratic},
//
//                                                    {"insertOpened_double",
//                                                    insertOpened_double},
//                                                    {"searchOpened_double",
//                                                    searchOpened_double},
//                                                    {"deleteOpened_double",
//                                                    deleteOpened_double},
//                                                    {"attemptsOpened_double",
//                                                    attemptsOpened_double},
//
//                                                    {"insertCocoo",
//                                                    insertCocoo},
//                                                    {"searchCocoo",
//                                                    searchCocoo},
//                                                    {"deleteCocoo",
//                                                    deleteCocoo},
//                                                    {"attemptsCocoo",
//                                                    attemptsCocoo},
//                                      };
//
//    write_csv(filepath, vals);
  };
