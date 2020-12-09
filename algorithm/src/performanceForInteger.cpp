#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <chrono>

#include "utils.h"
#include "LinkedHashMap.h"
#include "OpenedHashMap.h"

using namespace std;
using namespace std::chrono;

void getPerformanceInteger()
{
  const size_t tableSize = 10000;

  size_t testSize, vecSize = 5000;
  // cout << "\nEnter baseSize: ";
  // cin >> vecSize;
  cout << "\nEnter testSize: ";
  cin >> testSize;

  vector<int> baseVec, testVec;
  baseVec = genRandVec(vecSize, 0, 100000);
  testVec = genRandVec(testSize, 0, 100000);

  /*      Linked Hash Map part            */
  cout << "*****Linked Hash map*******" << endl;
  HashMap <int, int> hFixmap(tableSize);
  for(auto const& value: baseVec){
      // cout << "[" << value << "]" << endl;
      hFixmap.insert(value, value);
  }
  // test inserts
  auto start = high_resolution_clock::now();
  for(auto const& value: testVec){
      hFixmap.insert(value, value);
  }
  auto stop = high_resolution_clock::now();
  float duration = duration_cast<microseconds>(stop - start).count();
  cout << "Average insert time: "
            << duration / testSize << " microsec" << endl;
  // test search
  int value;
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


  /*      Opened Hash Map part          */
  cout << "\n*****Opened Hash map __LINEAR__*******" << endl;
  OpenHashMap<int, int> openHmap(tableSize, "LINEAR");
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
  OpenHashMap<int, int> openHmapDbl(tableSize,  "QUADRATIC");
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

//
// void getPerformanceIntegerLoop()
// {
//   size_t tableSize;
//   size_t testSize, vecSize;
//   vector<int> baseVec, testVec;
//   for (auto i=1; i<=50; ++i){
//
//     tableSize = 100 * i;
//     vecSize = tableSize / 2;
//     testSize = 50;
//     baseVec = genRandVec(vecSize, 0, 100000);
//     testVec = genRandVec(testSize, 0, 100000);
//
//     cout<<"\n*****M = "<< tableSize << ", N = " << vecSize << ", Actions = " << testSize
//              << " *****" << endl;
//     /*      Linked Hash Map part            */
//     cout << "Linked Hash map" << endl;
//     HashMap <int, int> hFixmap(tableSize);
//     for(auto const& value: baseVec){
//         hFixmap.insert(value, value);
//     }
//     // test inserts
//     auto start = high_resolution_clock::now();
//     for(auto const& value: testVec){
//         hFixmap.insert(value, value);
//     }
//     auto stop = high_resolution_clock::now();
//     float duration = duration_cast<microseconds>(stop - start).count();
//     cout << "Average insert time: "
//               << duration / testSize << " microsec" << endl;
//     // test search
//     int value;
//     start = high_resolution_clock::now();
//     for(auto const& key: testVec){
//       hFixmap.search(key, value);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     cout << "Average search time: "
//               << duration / testSize << " microsec" << endl;
//     // test delete
//     start = high_resolution_clock::now();
//     for(auto const& key: testVec){
//       hFixmap.remove(key);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     cout << "Average delete time: "
//               << duration / testSize << " microsec" << endl;
//
//
//     /*      Opened Hash Map part          */
//     cout << "\nOpened Hash map" << endl;
//     OpenHashMap<int, int> openHmap(tableSize);
//     for(auto const& value: baseVec){
//         openHmap.insert(value, value);
//     }
//     // test inserts
//     start = high_resolution_clock::now();
//     for(auto const& value: testVec){
//         openHmap.insert(value, value);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     cout << "Average insert time: "
//               << duration / testSize << " microsec" << endl;
//     // test search
//     start = high_resolution_clock::now();
//     for(auto const& key: testVec){
//       openHmap.search(key, value);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     cout << "Average search time: "
//               << duration / testSize << " microsec" << endl;
//     // test delete
//     start = high_resolution_clock::now();
//     for(auto const& key: testVec){
//       openHmap.remove(key);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     cout << "Average delete time: "
//               << duration / testSize << " microsec" << endl;
//
//
//   /*      CoCoo Hash Map part          */
//
//   }
//
// };
//
//
// void getPerformanceIntegerToFile()
// {
//   size_t tableSize;
//   size_t testSize, vecSize;
//   vector<int> baseVec, testVec;
//
//
//   string filepath = "../data/output/integerPerformanceM2N.csv";
//   vector<string> HashTableSize, DataSize;
//   vector<string> insertLinkedTime, insertOpenedTime, insertCocooTime;
//   vector<string> searchLinkedTime, searchOpenedTime, searchCocooTime;
//   vector<string> deleteLinkedTime, deleteOpenedTime, deleteCocooTime;
//
//   for (auto i=1; i<=1000; ++i){
//
//     tableSize = 100 * i;
//     vecSize = tableSize / 2;
//     testSize = 50;
//     baseVec = genRandVec(vecSize, 0, 100000);
//     testVec = genRandVec(testSize, 0, 100000);
//
//     HashTableSize.push_back(to_string(tableSize));
//     DataSize.push_back(to_string(vecSize));
//
//     HashMap <int, int> hFixmap(tableSize);
//     for(auto const& value: baseVec){
//         hFixmap.insert(value, value);
//     }
//     // test inserts
//     auto start = high_resolution_clock::now();
//     for(auto const& value: testVec){
//         hFixmap.insert(value, value);
//     }
//     auto stop = high_resolution_clock::now();
//     float duration = duration_cast<microseconds>(stop - start).count();
//     insertLinkedTime.push_back(to_string(duration / testSize));
//
//     // test search
//     int value;
//     start = high_resolution_clock::now();
//     for(auto const& key: testVec){
//       hFixmap.search(key, value);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     searchLinkedTime.push_back(to_string(duration / testSize));
//
//     // test delete
//     start = high_resolution_clock::now();
//     for(auto const& key: testVec){
//       hFixmap.remove(key);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     deleteLinkedTime.push_back(to_string(duration / testSize));
//
//
//     /*      Opened Hash Map part          */
//     OpenHashMap<int, int> openHmap(tableSize);
//     for(auto const& value: baseVec){
//         openHmap.insert(value, value);
//     }
//     // test inserts
//     start = high_resolution_clock::now();
//     for(auto const& value: testVec){
//         openHmap.insert(value, value);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     insertOpenedTime.push_back(to_string(duration / testSize));
//
//     // test search
//     start = high_resolution_clock::now();
//     for(auto const& key: testVec){
//       openHmap.search(key, value);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     searchOpenedTime.push_back(to_string(duration / testSize));
//
//     // test delete
//     start = high_resolution_clock::now();
//     for(auto const& key: testVec){
//       openHmap.remove(key);
//     }
//     stop = high_resolution_clock::now();
//     duration = duration_cast<microseconds>(stop - start).count();
//     deleteOpenedTime.push_back(to_string(duration / testSize));
//
//
//   /*      CoCoo Hash Map part          */
//
//   }
//
//   vector<pair<string,
//               vector<string>>> vals = {   {"TableSize", HashTableSize},
//                                           {"DataSize", DataSize},
//                                           {"insertLinkedTime", insertLinkedTime},
//                                           {"searchLinkedTime", searchLinkedTime},
//                                           {"deleteLinkedTime", deleteLinkedTime},
//                                           {"insertOpenedTime", insertOpenedTime},
//                                           {"searchOpenedTime", searchOpenedTime},
//                                           {"deleteOpenedTime", deleteOpenedTime},
//                                       };
//
//   write_csv(filepath, vals);
//
// };
