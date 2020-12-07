#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <random>

#include "utils.h"
#include "OpenedHashMap.h"

std::map<bool, std::string> oresult = {{false, "FAILED" }, { true, "PASSED" }};

void unitTestOpenHashMap(){
  std::cout << "\n\n*****Unit tets: Opened Hash map*******" << std::endl;

  //test 1
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const size_t tableSize = 10;
  OpenHashMap<int, int> openedHmap(tableSize);
  for(auto const& value: v){
      openedHmap.insert(value, value);
  }
  bool result = openedHmap.insert(11, 11);
  std::cout << "\nTest 1 is " << oresult[!result];

  // test 2
  v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  OpenHashMap<int, int> openedHmap2(tableSize);
  for(auto const& value: v){
      openedHmap2.insert(value, value);
  }
  int value;
  result = openedHmap2.search(3, value);
  result = result && (value == 3);
  std::cout << "\nTest 2 is " << oresult[result];

  // test 3
  v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  OpenHashMap<int, int> openedHmap3(tableSize);
  for(auto const& value: v){
      openedHmap3.insert(value, value);
  }
  result = openedHmap3.search(7, value);
  result = result && (value == 7);
  std::cout << "\nTest 3 is " << oresult[result];

  // test 4
  v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  OpenHashMap<int, int> openedHmap4(tableSize);
  for(auto const& value: v){
      openedHmap4.insert(value, value);
  }
  bool result1 = openedHmap4.search(5, value);
  openedHmap4.remove(5);
  result = result1 && !(openedHmap4.search(5, value));

  std::cout << "\nTest 4 is " << oresult[result];


};
