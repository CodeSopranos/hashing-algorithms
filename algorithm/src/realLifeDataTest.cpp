#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1

#include <chrono>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

// standart maps
#include <hash_map>
#include <map>

// our implementation
#include "ChainedHashMap.h"
#include "OpenedHashMap.h"
#include "utils.h"
#include "auxPerformance.h"

using namespace std;
using namespace std::chrono;



void realLifeDataTets(){
  // read csv
  string filepath1 = "../data/input/dictionary.csv";
  string filepath2 = "../data/input/test_dictionary.csv";
  vector<pair<string, vector<string>>> file1, file2;
  file1 = read_csv(filepath1);
  file2 = read_csv(filepath2);
  // for (auto i : file[1].second)
  //   cout << i << ' ';
  vector <string> dictionary = file1[1].second;
  vector <string> testWords = file2[1].second;

  size_t tableSize = dictionary.size()*1.2;
  size_t testSize = testWords.size();

  cout << "\n*******STD::MAP*************" << endl;
  std::map<string, string> stdMap;
  for (auto const &value : dictionary) {
    // cout << "[" << value << "]" << endl;
    stdMap.insert(std::make_pair(value, value));
  }
  // test inserts
  auto start = high_resolution_clock::now();
  for (auto const &value : testWords) {
    stdMap.insert(std::make_pair(value, value));
  }
  auto stop = high_resolution_clock::now();
  float duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;

  //test search
  std::map<string, string>::iterator it;
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    it = stdMap.find(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    stdMap.erase(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;

  /*      std::map part            */
  cout << "\n*******STD::HASH_MAP*************" << endl;
  std::hash_map<string, string> stdHashMap;
  for (auto const &value : dictionary) {
    // cout << "[" << value << "]" << endl;
    stdHashMap.insert(std::make_pair(value, value));
  }
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testWords) {
    stdHashMap.insert(std::make_pair(value, value));
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;

  //test search
  std::hash_map<string, string>::iterator hit;
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    hit = stdHashMap.find(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    stdHashMap.erase(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;

  /*      Chained Hash Map part            */
  cout << "\n*****Chained Hash map*******" << endl;
  HashMap<string, string> chainedHmap(tableSize);
  for (auto const &value : dictionary) {
    // cout << "[" << value << "]" << endl;
    chainedHmap.insert(value, value);
  }
  chainedHmap.resetCollisions();
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testWords) {
    chainedHmap.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  string value;
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    chainedHmap.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    chainedHmap.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;
  cout << "N attempts per operation: " << chainedHmap.getNumberOfCollisions() / (testSize * 3) << endl;

  cout << "\n*****Opened Hash map __QUADRATIC__*******" << endl;
  OpenHashMap<string, string> openHmapQdr(tableSize, "QUADRATIC");
  for (auto const &value : dictionary) {
    openHmapQdr.insert(value, value);
  }
  openHmapQdr.resetCollisions();
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testWords) {
    openHmapQdr.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    openHmapQdr.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    openHmapQdr.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;
  cout << "N attempts: " << openHmapQdr.getNumberOfCollisions() / (testSize * 3) << endl;

  cout << "\n*****Opened Hash map __DOUBLE__*******" << endl;
  OpenHashMap<string, string> openHmapDbl(tableSize, "DOUBLE");
  for (auto const &value : dictionary) {
    openHmapDbl.insert(value, value);
  }
  openHmapDbl.resetCollisions();
  // test inserts
  start = high_resolution_clock::now();
  for (auto const &value : testWords) {
    openHmapDbl.insert(value, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: " << duration / testSize << " microsec" << endl;
  // test search
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    openHmapDbl.search(key, value);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average search time: " << duration / testSize << " microsec" << endl;
  // test delete
  start = high_resolution_clock::now();
  for (auto const &key : testWords) {
    openHmapDbl.remove(key);
  }
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average delete time: " << duration / testSize << " microsec" << endl;
  cout << "N attempts: " << openHmapDbl.getNumberOfCollisions() / (testSize * 3) << endl;

};
