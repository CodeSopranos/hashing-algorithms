#pragma once


void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset);
std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename);

std::vector<int> genRandVec(int N, unsigned int a, unsigned int b);

void testNumberLinkedHashMap();
void testVectorLinkedHashMap();
