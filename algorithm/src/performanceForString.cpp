#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1

#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <chrono>

// standart maps
#include <map>
#include <hash_map>

#include "utils.h"
#include "ChainedHashMap.h"
#include "OpenedHashMap.h"

using namespace std;
using namespace std::chrono;

void getPerformanceString()
{
  const size_t tableSize = 5001;

  size_t testSize, vecSize = 2001;
  // cout << "\nEnter baseSize: ";
  // cin >> vecSize;
  cout << "\nEnter testSize: ";
  cin >> testSize;

  vector<string> baseVec, testVec;
  baseVec = genRandStrings(vecSize);
  testVec = genRandStrings(testSize);

  /*      std::map part            */
  cout << "\n*******STD::MAP*************" << endl;
  std::map<string, string> stdMap;
  for(auto const& value: baseVec){
      // cout << "[" << value << "]" << endl;
      stdMap.insert(std::make_pair(value, value));
  }
  // test inserts
  auto start = high_resolution_clock::now();
  for(auto const& value: testVec){
      stdMap.insert(std::make_pair(value, value));
  }
  auto stop = high_resolution_clock::now();
  float duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: "
            << duration / testSize << " microsec" << endl;

  // test search
  std::map<string, string>::iterator it;
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    it = stdMap.find(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: "
            << duration / testSize << " microsec" << endl;
   // test delete
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    stdMap.erase(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: "
            << duration / testSize << " microsec" << endl;


   /*      std::map part            */
  cout << "\n*******STD::HASH_MAP*************" << endl;
  std::hash_map<string, string> stdHashMap;
  for(auto const& value: baseVec){
      // cout << "[" << value << "]" << endl;
      stdHashMap.insert(std::make_pair(value, value));
  }
  // test inserts
  start = high_resolution_clock::now();
  for(auto const& value: testVec){
      stdHashMap.insert(std::make_pair(value, value));
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: "
            << duration / testSize << " microsec" << endl;

  // test search
  std::hash_map<string, string>::iterator hit;
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    hit = stdHashMap.find(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: "
            << duration / testSize << " microsec" << endl;
   // test delete
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    stdHashMap.erase(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: "
            << duration / testSize << " microsec" << endl;

  /*      Chained Hash Map part            */
  cout << "\n*****Chained Hash map*******" << endl;
  HashMap <string, string> hFixmap(tableSize);
  for(auto const& value: baseVec){
      // cout << "[" << value << "]" << endl;
      hFixmap.insert(value, value);
  }
  // test inserts
  start = high_resolution_clock::now();
  for(auto const& value: testVec){
      hFixmap.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: "
            << duration / testSize << " microsec" << endl;
  // test search
  string value;
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    hFixmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: "
            << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    hFixmap.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: "
            << duration / testSize << " microsec" << endl;
  //
  //
  /*      Opened Hash Map part          */
  cout << "\n*****Opened Hash map __LINEAR__*******" << endl;
  OpenHashMap<string, string> openHmap(tableSize, "LINEAR");
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
  cout << "Average insert time: "
            << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openHmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: "
            << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openHmap.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: "
            << duration / testSize << " microsec" << endl;

  cout << "\n*****Opened Hash map __QUADRATIC__*******" << endl;
  OpenHashMap<string, string> openHmapQdr(tableSize,  "QUADRATIC");
  for(auto const& value: baseVec){
      openHmapQdr.insert(value, value);
  }
  // test inserts
  start = high_resolution_clock::now();
  for(auto const& value: testVec){
      openHmapQdr.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: "
            << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openHmapQdr.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: "
            << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openHmapQdr.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: "
            << duration / testSize << " microsec" << endl;

  cout << "\n*****Opened Hash map __DOUBLE__*******" << endl;
  OpenHashMap<string, string> openHmapDbl(tableSize,  "DOUBLE");
  for(auto const& value: baseVec){
      openHmapDbl.insert(value, value);
  }
  // test inserts
  start = high_resolution_clock::now();
  for(auto const& value: testVec){
      openHmapDbl.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: "
            << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openHmapDbl.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: "
            << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for(auto const& key: testVec){
    openHmapDbl.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: "
            << duration / testSize << " microsec" << endl;


  /*      CoCoo Hash Map part          */


};
