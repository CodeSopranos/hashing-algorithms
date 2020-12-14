#pragma once

#define ITERATIONS 100
#define COEFFICIENT 2
#define OPERATIONS 30

// files utils
void write_csv(
    std::string filename,
    std::vector<std::pair<std::string, std::vector<std::string>>> dataset);
std::vector<std::pair<std::string, std::vector<std::string>>>
read_csv(std::string filename);

// random generators
std::vector<int> genRandVec(size_t N, unsigned int a, unsigned int b);
std::string genRandString(size_t);
std::vector<std::string> genRandStrings(size_t);
int genRandomUid(unsigned int a, unsigned int b);

// unit tests
void unitTestOpenHashMap();
bool unitTestCuckooHashMap(bool verbose);
bool unitTestCuckooHashMapStrings(bool verbose, int testVecSize, int baseVecSize);
void unitTestChainedHashMap();

// stress tests
void stressTestChainedHashMap();
void stressTestOpenHashMap();
void stressTestCuckooHashMap();

// performance evaluation int
void getPerformanceInteger();
void getPerformanceIntegerToFile();

// performance evaluation string
void getPerformanceString();
void getPerformanceStringToFile();

//real life data tests
void realLifeDataTets();
