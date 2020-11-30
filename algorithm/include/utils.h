#pragma once


void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset);
std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename);

std::vector<int> gen_rand_vec(int N);
