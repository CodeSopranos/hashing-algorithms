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
  OpenHashMap<int, int, tableSize> openedHmap;
  for(auto const& value: baseVec){
      openedHmap.insert(value, value);
  }
  // test inserts
  start = high_resolution_clock::now();
  for(auto const& value: testVec){
      openedHmap.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  std::cout << "Average insert time: "
            << duration / testSize << " microsec" << std::endl;
  // test search
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openedHmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  std::cout << "Average search time: "
            << duration / testSize << " microsec" << std::endl;
  // test delete
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openedHmap.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  std::cout << "Average delete time: "
            << duration / testSize << " microsec" << std::endl;


  /*      CoCoo Hash Map part          */


};
