#pragma once
#include <math.h>
#include <random>
#include <string>

template <typename K> class KeyHash {
private:
  size_t tableSize;

public:
  KeyHash(size_t tableSize) : tableSize(tableSize) {}

  unsigned int operator[](const K &key) const {
    return (key) % this->tableSize;
  }
};

template <> class KeyHash<int> {
private:
  size_t tableSize;
  unsigned int a, b;
  unsigned int prime = 150001;

public:
  KeyHash(size_t tableSize) {
    this->tableSize = tableSize;
    std::random_device randDev;
    std::mt19937 mers(randDev());
    std::uniform_int_distribution<int> a_uid(1, prime - 1);
    std::uniform_int_distribution<int> b_uid(0, prime - 1);
    this->a = a_uid(mers);
    this->b = b_uid(mers);
  }
  unsigned int operator[](const int &key) const {
    unsigned int l = a * key + b;
    if (l >= tableSize) {
      l = (l >= prime) ? l % prime : l;
      return (l >= tableSize) ? (l % tableSize) : l;
    } else {
      return l;
    }
  }
};

template <> class KeyHash<std::string> {
private:
  size_t tableSize;
public:
  KeyHash(size_t tableSize) {
    this->tableSize = tableSize;
    std::random_device randDev;
  }
  unsigned int operator[](const std::string key) const {
    unsigned int hkey = 0;//5381;
    for (auto i = 0; i < key.size(); ++i) {
      hkey = ((hkey << 5)+hkey) + key[i];
    }
    return (hkey >= tableSize) ? hkey % tableSize : hkey;
  }
};
