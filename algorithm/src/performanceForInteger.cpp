#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <chrono>

#include "utils.h"
#include "LinkedHashMap.h"
#include "OpenedHashMap.h"


using namespace std::chrono;

void getPerformanceInteger()
{
  const size_t tableSize = 5000;

  std::size_t testSize, vecSize = 2500;
  // std::cout << "\nEnter baseSize: ";
  // std::cin >> vecSize;
  std::cout << "\nEnter testSize: ";
  std::cin >> testSize;

  std::vector<int> baseVec, testVec;
  baseVec = genRandVec(vecSize, 0, 100000);
  testVec = genRandVec(testSize, 0, 100000);

  /*      Linked Hash Map part            */
  std::cout << "*****Linked Hash map*******" << std::endl;
  HashMap <int, int> hFixmap(tableSize);
  for(auto const& value: baseVec){
      // std::cout << "[" << value << "]" << std::endl;
      hFixmap.insert(value, value);
  }
  // test inserts
  auto start = high_resolution_clock::now();
  for(auto const& value: testVec){
      hFixmap.insert(value, value);
  }
  auto stop = high_resolution_clock::now();
  float duration = duration_cast<microseconds>(stop - start).count();
  std::cout << "Average insert time: "
            << duration / testSize << " microsec" << std::endl;
  // test search
  int value;
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    hFixmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  std::cout << "Average search time: "
            << duration / testSize << " microsec" << std::endl;
  // test delete
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    hFixmap.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  std::cout << "Average delete time: "
            << duration / testSize << " microsec" << std::endl;


  /*      Opened Hash Map part          */
  std::cout << "\n*****Opened Hash map*******" << std::endl;
  OpenHashMap<int, int> openHmap(tableSize);
  for(auto const& value: baseVec){
      openHmap.insert(value, value);
  }
  // test inserts
  start = high_resolution_clock::now();
  for(auto const& value: testVec){
      openHmap.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  std::cout << "Average insert time: "
            << duration / testSize << " microsec" << std::endl;
  // test search
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openHmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  std::cout << "Average search time: "
            << duration / testSize << " microsec" << std::endl;
  // test delete
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openHmap.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  std::cout << "Average delete time: "
            << duration / testSize << " microsec" << std::endl;
  /*      CoCoo Hash Map part          */


};


void getPerformanceIntegerLoop()
{
  size_t tableSize;
  std::size_t testSize, vecSize;
  std::vector<int> baseVec, testVec;
  for (auto i=1; i<=50; ++i){

    tableSize = 100 * i;
    vecSize = tableSize / 2;
    testSize = 50;
    baseVec = genRandVec(vecSize, 0, 100000);
    testVec = genRandVec(testSize, 0, 100000);

    std::cout<<"\n*****M = "<< tableSize << ", N = " << vecSize << ", Actions = " << testSize
             << " *****" << std::endl;
    /*      Linked Hash Map part            */
    std::cout << "Linked Hash map" << std::endl;
    HashMap <int, int> hFixmap(tableSize);
    for(auto const& value: baseVec){
        hFixmap.insert(value, value);
    }
    // test inserts
    auto start = high_resolution_clock::now();
    for(auto const& value: testVec){
        hFixmap.insert(value, value);
    }
    auto stop = high_resolution_clock::now();
    float duration = duration_cast<microseconds>(stop - start).count();
    std::cout << "Average insert time: "
              << duration / testSize << " microsec" << std::endl;
    // test search
    int value;
    start = high_resolution_clock::now();
    for(auto const& key: testVec){
      hFixmap.search(key, value);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    std::cout << "Average search time: "
              << duration / testSize << " microsec" << std::endl;
    // test delete
    start = high_resolution_clock::now();
    for(auto const& key: testVec){
      hFixmap.remove(key);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    std::cout << "Average delete time: "
              << duration / testSize << " microsec" << std::endl;


    /*      Opened Hash Map part          */
    std::cout << "\nOpened Hash map" << std::endl;
    OpenHashMap<int, int> openHmap(tableSize);
    for(auto const& value: baseVec){
        openHmap.insert(value, value);
    }
    // test inserts
    start = high_resolution_clock::now();
    for(auto const& value: testVec){
        openHmap.insert(value, value);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    std::cout << "Average insert time: "
              << duration / testSize << " microsec" << std::endl;
    // test search
    start = high_resolution_clock::now();
    for(auto const& key: testVec){
      openHmap.search(key, value);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    std::cout << "Average search time: "
              << duration / testSize << " microsec" << std::endl;
    // test delete
    start = high_resolution_clock::now();
    for(auto const& key: testVec){
      openHmap.remove(key);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    std::cout << "Average delete time: "
              << duration / testSize << " microsec" << std::endl;


  /*      CoCoo Hash Map part          */

  }

};


void getPerformanceIntegerToFile()
{
  size_t tableSize;
  std::size_t testSize, vecSize;
  std::vector<int> baseVec, testVec;


  std::string filepath = "../data/output/integerPerformanceM2N.csv";
  std::vector<std::string> HashTableSize, DataSize;
  std::vector<std::string> insertLinkedTime, insertOpenedTime, insertCocooTime;
  std::vector<std::string> searchLinkedTime, searchOpenedTime, searchCocooTime;
  std::vector<std::string> deleteLinkedTime, deleteOpenedTime, deleteCocooTime;

  for (auto i=1; i<=1000; ++i){

    tableSize = 100 * i;
    vecSize = tableSize / 2;
    testSize = 50;
    baseVec = genRandVec(vecSize, 0, 100000);
    testVec = genRandVec(testSize, 0, 100000);

    HashTableSize.push_back(std::to_string(tableSize));
    DataSize.push_back(std::to_string(vecSize));

    HashMap <int, int> hFixmap(tableSize);
    for(auto const& value: baseVec){
        hFixmap.insert(value, value);
    }
    // test inserts
    auto start = high_resolution_clock::now();
    for(auto const& value: testVec){
        hFixmap.insert(value, value);
    }
    auto stop = high_resolution_clock::now();
    float duration = duration_cast<microseconds>(stop - start).count();
    insertLinkedTime.push_back(std::to_string(duration / testSize));

    // test search
    int value;
    start = high_resolution_clock::now();
    for(auto const& key: testVec){
      hFixmap.search(key, value);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    searchLinkedTime.push_back(std::to_string(duration / testSize));

    // test delete
    start = high_resolution_clock::now();
    for(auto const& key: testVec){
      hFixmap.remove(key);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    deleteLinkedTime.push_back(std::to_string(duration / testSize));


    /*      Opened Hash Map part          */
    OpenHashMap<int, int> openHmap(tableSize);
    for(auto const& value: baseVec){
        openHmap.insert(value, value);
    }
    // test inserts
    start = high_resolution_clock::now();
    for(auto const& value: testVec){
        openHmap.insert(value, value);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    insertOpenedTime.push_back(std::to_string(duration / testSize));

    // test search
    start = high_resolution_clock::now();
    for(auto const& key: testVec){
      openHmap.search(key, value);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    searchOpenedTime.push_back(std::to_string(duration / testSize));

    // test delete
    start = high_resolution_clock::now();
    for(auto const& key: testVec){
      openHmap.remove(key);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start).count();
    deleteOpenedTime.push_back(std::to_string(duration / testSize));


  /*      CoCoo Hash Map part          */

  }

  std::vector<std::pair<std::string,
              std::vector<std::string>>> vals = {   {"TableSize", HashTableSize},
                                                    {"DataSize", DataSize},
                                                    {"insertLinkedTime", insertLinkedTime},
                                                    {"searchLinkedTime", searchLinkedTime},
                                                    {"deleteLinkedTime", deleteLinkedTime},
                                                    {"insertOpenedTime", insertOpenedTime},
                                                    {"searchOpenedTime", searchOpenedTime},
                                                    {"deleteOpenedTime", deleteOpenedTime},
                                                  };

  write_csv(filepath, vals);

};
