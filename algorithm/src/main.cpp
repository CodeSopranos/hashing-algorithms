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
  // read csv
  /*
  std::vector<std::pair<std::string, std::vector<int>>> file =
  read_csv(filepath); for (int i = 0; i < file.size(); i++)
  {
      std::cout << file[i].first << ": ";

      for (auto i : file[i].second)
          std::cout << i << ' ';

      std:cout << endl;
  }
  */

  // unit tests
  unitTestChainedHashMap();
  unitTestOpenHashMap();

  // performance evaluation
  std::cout << "\n\n****Integer Numbers Hashing******";
  getPerformanceInteger();
  // getPerformanceIntegerLoop();
  // getPerformanceIntegerToFile();

  std::cout << "\n\n****Strings  Hashing******";
  getPerformanceString();

  // size_t N = 100;
  // // std::vector<std::string> sample;
  // auto sample = genRandStrings(N);
  // for(auto const& value: sample){
  //     std::cout << value << std::endl;
  //     // hmap.insert(value, value);
  // }

  // std::cout << "\n\nUnit test OPEN hash \n\n";
  // std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // std::vector<int> t = {3, 4, 5, 9, 10, 20, 21, 6};
  // size_t tableSize = 9;
  //
  // OpenHashMap<int, int> hmap(tableSize, "LINEAR");
  // hmap.displayHash();
  // for(auto const& value: v){
  //     // std::cout << value << " ";
  //     hmap.insert(value, value);
  // }
  // hmap.displayHash();
  // int value;
  // for(auto const& key: t){
  //     // std::cout << value << " ";
  //     if(hmap.search(key, value)){
  //       std::cout<<" found " << key <<" "<< value<<std::endl;
  //     }
  //     else{
  //         std::cout<<key<<" not found "<<std::endl;
  // }
  //
  // }
  // for(auto const& value: t){
  //     // std::cout << value << " ";
  //     hmap.remove(value);
  // }
  // hmap.displayHash();
  //
  // for(auto const& value: v){
  //     // std::cout << value << " ";
  //     hmap.remove(value);
  // }
  // hmap.displayHash();
  //
  // for(auto const& value: v){
  //     // std::cout << value << " ";
  //     hmap.insert(value, value);
  // }
  // hmap.displayHash();

  // std::cout << "\n\nUnit test OPEN hash STRING \n\n";
  // std::vector<std::string> vs = {"111", "244", "1", "99412", "aavsa", "a",
  // "vdasr", "hello", "1sa11rf4f5", "end" }; std::vector<std::string> ts =
  // {"244", "1", "99412", "aavsa", "a", "vdasr", "NO", "ALSO NO"}; size_t
  // tableSize = 9;
  //
  // OpenHashMap<std::string, std::string> shmap(tableSize, "LINEAR");
  // shmap.displayHash();
  // for(auto const& value: vs){
  //     // std::cout << value << " ";
  //     shmap.insert(value, value);
  // }
  // shmap.displayHash();
  // std::string svalue;
  // for(auto const& key: ts){
  //     // std::cout << value << " ";
  //     if(shmap.search(key, svalue)){
  //       std::cout<<" found " << key <<" "<< svalue<<std::endl;
  //     }
  //     else{
  //         std::cout<<key<<" not found "<<std::endl;
  // }
  //
  // }
  // for(auto const& value: ts){
  //     // std::cout << value << " ";
  //     shmap.remove(value);
  // }
  // shmap.displayHash();
  //
  // for(auto const& value: vs){
  //     // std::cout << value << " ";
  //     shmap.remove(value);
  // }
  // shmap.displayHash();
  //
  // for(auto const& value: vs){
  //     // std::cout << value << " ";
  //     shmap.insert(value, value);
  // }
  // shmap.displayHash();

  return 0;
}
