#pragma once

// files utils
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<std::string>>> dataset);
std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename);

// random generators
std::vector<int> genRandVec(size_t N, unsigned int a, unsigned int b);
std::string genRandString(size_t);
std::vector<std::string> genRandStrings(size_t);

// unit tests
void unitTestOpenHashMap();
void unitTestChainedHashMap();

// performance evaluation
void getPerformanceInteger();
void getPerformanceIntegerLoop();
void getPerformanceIntegerToFile();

void getPerformanceString();
// void testVectorLinkedHashMap();
