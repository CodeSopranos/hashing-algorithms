#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "ChainedHashMap.h"
#include "utils.h"

std::map<bool, std::string> tresult = {{false, "FAILED"}, {true, "PASSED"}};

void unitTestChainedHashMap() {

  std::cout << "\n*****Unit tets: Chained Hash map*******" << std::endl;

  // test 1
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const size_t tableSize = 10;
  HashMap<int, int> hmap(tableSize);
  for (auto const &value : v) {
    hmap.insert(value, value);
  }
  bool result = hmap.insert(11, 11);
  std::cout << "\nTest 1 is " << tresult[result];

  // test 2
  v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  HashMap<int, int> hmap2(tableSize);
  for (auto const &value : v) {
    hmap2.insert(value, value);
  }
  int value;
  result = hmap2.search(3, value);
  result = result && (value == 3);
  std::cout << "\nTest 2 is " << tresult[result];

  // test 3
  v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  HashMap<int, int> hmap3(tableSize);
  for (auto const &value : v) {
    hmap3.insert(value, value);
  }
  result = hmap3.search(7, value);
  result = result && (value == 7);
  std::cout << "\nTest 3 is " << tresult[result];

  // test 4
  v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  HashMap<int, int> hmap4(tableSize);
  for (auto const &value : v) {
    hmap4.insert(value, value);
  }
  bool result1 = hmap4.search(5, value);
  hmap4.remove(5);
  result = result1 && !(hmap4.search(5, value));

  std::cout << "\nTest 4 is " << tresult[result];
};
