#pragma once

// files utils
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset);
std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename);

// random generators
std::vector<int> genRandVec(int N, unsigned int a, unsigned int b);

// unit tests
void unitTestOpenHashMap();
//
// performance evaluation
void getPerformanceInteger();
// void testVectorLinkedHashMap();
