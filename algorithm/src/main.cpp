#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "utils.h"
#include "ChainedHashMap.h"
#include "OpenedHashMap.h"
#include "CuckooHashMap.h"


int main() {

  // unit tests
  unitTestChainedHashMap();
  unitTestOpenHashMap();
  unitTestCuckooHashMap();

  //stress tests
  stressTestChainedHashMap();
  stressTestOpenHashMap();
  stressTestCuckooHashMap();

  // performance evaluation
  std::cout << "\n\n****Integer Numbers Hashing****";
  // getPerformanceInteger();
  getPerformanceIntegerToFile();

  std::cout << "\n\n****Strings  Hashing****";
  // getPerformanceString();
  getPerformanceStringToFile();

  // real life data
  std::cout << "\n\n***Real life data hashing***\n";
  realLifeDataTets();

  return 0;
}
