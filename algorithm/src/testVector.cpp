#include <iostream>
#include <vector>
#include <random>

#include "utils.h"
#include "HashMap.h"


void testVectorLinkedHashMap()
{
  std::cout << "\nEnter tableSize: ";
  const auto tableSize = 71;// = [](int t){ return std::cin >> t, t; }({});

  std::size_t vecSize, itemSize;
  std::cout << "\nEnter vecSize: ";
  std::cin >> vecSize;
  std::cout << "\nEnter itemSize: ";
  std::cin >> itemSize;
  std::vector<std::vector<int>> randVec;
  for(auto i=0; i < vecSize; i++)
    randVec.push_back(genRandVec(itemSize));

  // building hashMap
  HashMap <std::vector<int>, std::vector<int>, tableSize> hmap;
  for(auto const& vec: randVec){
      std::cout << "[ ";
      for(auto const& value: vec)
      {
        std::cout << value << " ";
      }
      std::cout << "]"<<std::endl;
      hmap.insert(vec, vec);
  }

  while(true){
    int index;
    std::vector<int> value(itemSize);
    std::cout << "\nEnter index of vector: ";
    std::cin >> index;
    if (index == -1){
      break;
    }
    hmap.search(randVec[index], value);
  }

}
