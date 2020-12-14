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
#include "OpenedHashMap.h"
#include "utils.h"
#include "auxPerformance.h"

using namespace std;
using namespace std::chrono;

void getPerformanceString() {
  const size_t tableSize = 10000;

  size_t testSize, vecSize = 7000;
  // cout << "\nEnter baseSize: ";
  // cin >> vecSize;
  cout << "\nEnter testSize: ";
  cin >> testSize;

  vector<string> baseVec, testVec;
  baseVec = genRandStrings(vecSize);
  testVec = genRandStrings(testSize);

  /*      std::map part            */
  cout << "\n*******STD::MAP*************" << endl;
  std::map<string, string> stdMap;
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
  std::map<string, string>::iterator it;
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
  std::hash_map<string, string> stdHashMap;
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
  std::hash_map<string, string>::iterator hit;
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
  cout << "\n*****Chained Hash map*******" << endl;
  HashMap<string, string> chainedHmap(tableSize);
  for (auto const &value : baseVec) {
    // cout << "[" << value << "]" << endl;
    chainedHmap.insert(value, value);
  }
  chainedHmap.resetCollisions();
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    chainedHmap.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  string value;
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    chainedHmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    chainedHmap.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;
  cout << "N attempts per operation: " << chainedHmap.getNcollisions() / (testSize * 3) << endl;

  /*      Opened Hash Map part          */
  cout << "\n*****Opened Hash map __LINEAR__*******" << endl;
  OpenHashMap<string, string> openHmap(tableSize, "LINEAR");
  for (auto const &value : baseVec) {
    openHmap.insert(value, value);
  }
  openHmap.resetCollisions();
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    openHmap.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmap.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;
  cout << "N attempts: " << openHmap.getNcollisions() / (testSize * 3) << endl;

  cout << "\n*****Opened Hash map __QUADRATIC__*******" << endl;
  OpenHashMap<string, string> openHmapQdr(tableSize, "QUADRATIC");
  for (auto const &value : baseVec) {
    openHmapQdr.insert(value, value);
  }
  openHmapQdr.resetCollisions();
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    openHmapQdr.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapQdr.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapQdr.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;
  cout << "N attempts: " << openHmapQdr.getNcollisions() / (testSize * 3) << endl;

  cout << "\n*****Opened Hash map __DOUBLE__*******" << endl;
  OpenHashMap<string, string> openHmapDbl(tableSize, "DOUBLE");
  for (auto const &value : baseVec) {
    openHmapDbl.insert(value, value);
  }
  openHmapDbl.resetCollisions();
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testVec) {
    openHmapDbl.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapDbl.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testVec) {
    openHmapDbl.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;
  cout << "N attempts: " << openHmapDbl.getNcollisions() / (testSize * 3) << endl;
  /*      CoCoo Hash Map part          */
};


void getPerformanceStringToFile()
{
  size_t tableSize;
  size_t testSize, vecSize;
  vector<string> baseVec, testVec;
  string filepath = "../data/output/stringPerformanceM2N_1.csv";
  vector<string> HashTableSize, DataSize;

  vector<string> insertMap, insertHashMap;
  vector<string> searchMap, searchHashMap;
  vector<string> deleteMap, deleteHashMap;

  vector<string> attemptsChained, attemptsOpened_linear, attemptsOpened_quadratic, attemptsOpened_double, attemptsCocoo;

  vector<string> insertChained, insertOpened_linear, insertOpened_quadratic, insertOpened_double, insertCocoo;
  vector<string> searchChained, searchOpened_linear, searchOpened_quadratic, searchOpened_double, searchCocoo;
  vector<string> deleteChained, deleteOpened_linear, deleteOpened_quadratic, deleteOpened_double, deleteCocoo;

  typedef HashMap <string, string> strChainedHashMap;
  typedef OpenHashMap <string, string> strOpenedHashMap;
  cout << "\n\nProgress: ";
  for (auto i=1; i<=ITERATIONS; ++i){
    if (i % 10 == 0){
      cout<<"#";
    }
    tableSize = 100 * i;
    vecSize = tableSize / COEFFICIENT;
    testSize = OPERATIONS;
    baseVec = genRandStrings(vecSize);
    testVec = genRandStrings(testSize);

    HashTableSize.push_back(to_string(tableSize));
    DataSize.push_back(to_string(vecSize));

      /*      std::map part            */
    std::map<string, string> stdMap;
    for (auto const &value : baseVec) {
      stdMap.insert(std::make_pair(value, value));
    }
    // test inserts
    auto start = high_resolution_clock::now();
    for (auto const &value : testVec) {
      stdMap.insert(std::make_pair(value, value));
    }
    auto stop = high_resolution_clock::now();
    float duration = duration_cast<microseconds>(stop - start).count();
    insertMap.push_back(to_string(duration / testSize));
    // test search
    std::map<string, string>::iterator it;
    start = high_resolution_clock::now();
    for (auto const &key : testVec) {
      it = stdMap.find(key);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    searchMap.push_back(to_string(duration / testSize));
    // test delete
    start = high_resolution_clock::now();
    for (auto const &key : testVec) {
      stdMap.erase(key);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    deleteMap.push_back(to_string(duration / testSize));

    /*      std::hash_map part            */
    std::hash_map<string, string> stdHashMap;
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
    insertHashMap.push_back(to_string(duration / testSize));
    // test search
    std::hash_map<string, string>::iterator hit;
    start = high_resolution_clock::now();
    for (auto const &key : testVec) {
      hit = stdHashMap.find(key);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    searchHashMap.push_back(to_string(duration / testSize));
    // test delete
    start = high_resolution_clock::now();
    for (auto const &key : testVec) {
      stdHashMap.erase(key);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    deleteHashMap.push_back(to_string(duration / testSize));

    strChainedHashMap hmap(tableSize);
    for(auto const& value: baseVec){
        hmap.insert(value, value);
    }
    auxPerformanceFunc<strChainedHashMap, string>(hmap, testVec, insertChained, searchChained, deleteChained, attemptsChained);

    // strOpenedHashMap openedHmapL(tableSize, "LINEAR");
    // for(auto const& value: baseVec){
    //     openedHmapL.insert(value, value);
    // }
    // auxPerformanceFunc<strOpenedHashMap, string>(openedHmapL, testVec, insertOpened_linear, searchOpened_linear, deleteOpened_linear, attemptsOpened_linear);

    strOpenedHashMap openedHmapQ(tableSize, "QUADRATIC");
    for(auto const& value: baseVec){
        openedHmapQ.insert(value, value);
    }
    auxPerformanceFunc<strOpenedHashMap, string>(openedHmapQ, testVec, insertOpened_quadratic, searchOpened_quadratic, deleteOpened_quadratic, attemptsOpened_quadratic);

    strOpenedHashMap openedHmapD(tableSize, "DOUBLE");
    for(auto const& value: baseVec){
        openedHmapD.insert(value, value);
    }
    auxPerformanceFunc<strOpenedHashMap, string>(openedHmapD, testVec, insertOpened_double, searchOpened_double, deleteOpened_double, attemptsOpened_double);
  }
    vector<pair<string, vector<string>>> vals = {   {"TableSize", HashTableSize},
                                                    {"DataSize", DataSize},

                                                    {"insertStdMap",
                                                    insertMap},
                                                    {"searchStdMap",
                                                    searchMap},
                                                    {"deleteStdMap",
                                                    deleteMap},

                                                    {"insertStdHashMap",
                                                    insertHashMap},
                                                    {"searchStdHashMap",
                                                    searchHashMap},
                                                    {"deleteStdHashMap",
                                                    deleteHashMap},

                                                    {"insertChained",
                                                    insertChained},
                                                    {"searchChained",
                                                    searchChained},
                                                    {"deleteChained",
                                                    deleteChained},
                                                    {"attemptsChained",
                                                    attemptsChained},
                                                    // {"insertOpened_linear",
                                                    // insertOpened_linear},
                                                    // {"searchOpened_linear",
                                                    // searchOpened_linear},
                                                    // {"deleteOpened_linear",
                                                    // deleteOpened_linear},

                                                    {"insertOpened_quadratic",
                                                    insertOpened_quadratic},
                                                    {"searchOpened_quadratic",
                                                    searchOpened_quadratic},
                                                    {"deleteOpened_quadratic",
                                                    deleteOpened_quadratic},
                                                    {"attemptsOpened_quadratic",
                                                    attemptsOpened_quadratic},

                                                    {"insertOpened_double",
                                                    insertOpened_double},
                                                    {"searchOpened_double",
                                                    searchOpened_double},
                                                    {"deleteOpened_double",
                                                    deleteOpened_double},
                                                    {"attemptsOpened_double",
                                                    attemptsOpened_double},
                                      };

    write_csv(filepath, vals);
  };
