#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "utils.h"
// #include "ChainedHashMap.h"
#include "OpenedHashMap.h"

int main() {

  // unit tests
  unitTestChainedHashMap();
  unitTestOpenHashMap();

  //stress tests
  stressTestChainedHashMap();
  stressTestOpenHashMap();

  // performance evaluation
  std::cout << "\n\n****Integer Numbers Hashing****";
  // getPerformanceInteger();
  // getPerformanceIntegerLoop();
  getPerformanceIntegerToFile();

  std::cout << "\n\n****Strings  Hashing****";
  // getPerformanceString();
  getPerformanceStringToFile();

  // real life data
  std::cout << "\n\n***Real life data hashing***\n";
  realLifeDataTets();

  // std::cout<< (6 * 32) << " " << (6 << 5);



  return 0;
}
