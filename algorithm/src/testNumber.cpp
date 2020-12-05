#include <iostream>
#include <vector>
#include <random>

#include "utils.h"
#include "HashMap.h"


void testNumberLinkedHashMap()
{
  std::cout << "\nEnter tableSize: ";
  const auto tableSize = 71;

  std::size_t vecSize;
  std::cout << "\nEnter vecSize: ";
  std::cin >> vecSize;
  std::vector<int> randVec(vecSize);
  randVec = genRandVec(vecSize);

  // building hasgMap
  HashMap <int, int, tableSize> hmap;
  for(auto const& value: randVec){
      std::cout << value << std::endl;
      hmap.insert(value, value);
  }

  while(true){
    int value;
    std::cout << "\nEnter key: ";
    std::cin >> value;
    if (value == -1){
      break;
    }
    hmap.search(value, value);
  }

};