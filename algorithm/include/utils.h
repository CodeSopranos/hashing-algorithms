#pragma once

#define ITERATIONS 400
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

// unit tests
void unitTestOpenHashMap();
void unitTestChainedHashMap();

// stress tests
void stressTestChainedHashMap();
void stressTestOpenHashMap();

// performance evaluation int
void getPerformanceInteger();
void getPerformanceIntegerToFile();

// performance evaluation string
void getPerformanceString();
void getPerformanceStringToFile();

//real life data tests
void realLifeDataTets();
