#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <chrono>

#include "utils.h"
#include "LinkedHashMap.h"
#include "OpenedHashMap.h"

using namespace std::chrono;

void testNumberLinkedHashMap()
{
  const size_t tableSize = 500;

  std::size_t vecSize, testSize;
  std::cout << "\nEnter baseSize: ";
  std::cin >> vecSize;
  std::cout << "\nEnter testSize: ";
  std::cin >> testSize;
  std::vector<int> baseVec, testVec;
  baseVec = genRandVec(vecSize, 0, 1000);
  testVec = genRandVec(testSize, 0, 1000);

  /*      Linked Hash Map part            */
  HashMap <int, int, tableSize> hmap;
  for(auto const& value: baseVec){
      // std::cout << "[" << value << "]" << std::endl;
      hmap.insert(value, value);
  }
  // test inserts
  auto start = high_resolution_clock::now();
  for(auto const& value: testVec){
      hmap.insert(value, value);
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "Average insert time: "
            << duration.count()<< " microsec" << std::endl;
  // test search
  int value;
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    hmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  std::cout << "Average search time: "
            << duration.count()<< " microsec" << std::endl;
};
