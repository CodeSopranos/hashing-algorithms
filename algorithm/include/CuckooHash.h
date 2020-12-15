#pragma once
#include "UniversalHash.h"
#include "primeNumbers.h"
#include  "utils.h"
#include "primeNumbers.h"

template <typename K> class CuckooKeyHash {
private:
    size_t tableSize;
    KeyHash<K> uniHashFunc;
    unsigned int a, b;

public:
    CuckooKeyHash(size_t tableSize)
    : tableSize(tableSize),
      uniHashFunc(tableSize),
      a(genRandomUid(1, 12)),
      b(genRandomUid(0,  PRIME.size()-1))
      {};

    unsigned int operator[](const K &key) const {
        unsigned int l = (uniHashFunc[key] << a) + PRIME[b];
        return (l >= tableSize) ? l % tableSize : l;
    }
};


template<> class CuckooKeyHash<std::string>{
private:
    size_t tableSize;
    KeyHash<std::string> uniHashFunc;
    unsigned int a, b;

public:
    CuckooKeyHash(size_t tableSize)
    : tableSize(tableSize),
      uniHashFunc(tableSize),
      a(genRandomUid(1, 12)),
      b(genRandomUid(0, PRIME.size()-1))
      {};

    unsigned int operator[](const std::string &key) const {
        unsigned int l = PRIME[b];
        for (auto i = 0; i < key.size(); ++i) {
          l = ((l << a)+l) + key[i];
        }
        return (l >= tableSize) ? l % tableSize : l;
    }
};
