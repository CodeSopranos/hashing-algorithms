#pragma once
#include <math.h>
#include <random>
#include <string>

#include "UniversalHash.h"
#include "primeNumbers.h"


template <typename T> struct KeyAttempt {
  const T &key;
  unsigned int attempt;
};

template <typename K> class OpenKeyHash {
private:
  size_t tableSize;
  KeyHash<K> uniHashFunc;
  KeyHash<K> uniHashFuncAUX;
  unsigned int prime = 101027;
  unsigned int c1 = 1;
  unsigned int c2 = 3;
  std::string hashType;

public:
  OpenKeyHash(size_t tableSize, std::string hashType)
      : tableSize(tableSize),
        uniHashFunc(tableSize),
        uniHashFuncAUX(tableSize),
        hashType(hashType){};

  unsigned int operator[](KeyAttempt<K> const &pairKA) const {
    if (hashType == "LINEAR") {
      unsigned int l = uniHashFunc[pairKA.key] + pairKA.attempt;
      return (l >= tableSize) ? l % tableSize : l;
    } else if (hashType == "QUADRATIC") {
      unsigned int l = (uniHashFunc[pairKA.key] +
                       (c1 * pairKA.attempt)    +
                       (c2 * pairKA.attempt * pairKA.attempt));
      return  (l >= tableSize) ? l % tableSize : l;
    } else if (hashType == "DOUBLE") {
      unsigned int auxHash1 = uniHashFunc[pairKA.key];
      unsigned int auxHash2 = (PRIME[pairKA.key % 420]);//1 + (pairKA.key % 8);
      unsigned int l = auxHash1 + (pairKA.attempt * auxHash2);
      return (l >= tableSize) ? l % tableSize : l;
    } else {
      unsigned int l = uniHashFunc[pairKA.key] + pairKA.attempt;
      return (l >= tableSize) ? l % tableSize : l;
    }
  }
};

template <> class OpenKeyHash<std::string> {
private:
  size_t tableSize;
  KeyHash<std::string> uniHashFunc;
  KeyHash<std::string> uniHashFuncAUX;
  unsigned int prime = 97;
  unsigned int c1 = 1;
  unsigned int c2 = 3;
  std::string hashType;

public:
  OpenKeyHash(size_t tableSize, std::string hashType)
      : tableSize(tableSize), uniHashFunc(tableSize), uniHashFuncAUX(tableSize),
        hashType(hashType){};

  unsigned int operator[](KeyAttempt<std::string> const &pairKA) const {
    if (hashType == "LINEAR") {
      unsigned int l = uniHashFunc[pairKA.key] + pairKA.attempt;
      return (l >= tableSize) ? l % tableSize : l;
    } else if (hashType == "QUADRATIC") {
      unsigned int l = (uniHashFunc[pairKA.key] +
                       (c1 * pairKA.attempt)    +
                       (c2 * pairKA.attempt * pairKA.attempt));
      return  (l >= tableSize) ? l % tableSize : l;
    } else if (hashType == "DOUBLE") {
      unsigned int auxHash1 = uniHashFunc[pairKA.key];
      unsigned int auxHash2 = PRIME[pairKA.key[0]+pairKA.key[pairKA.key.size()-1]];
      unsigned int l = auxHash1 + pairKA.attempt * auxHash2;
      return (l >= tableSize) ? l % tableSize : l;
    } else {
      unsigned int l = uniHashFunc[pairKA.key] + pairKA.attempt;
      return (l >= tableSize) ? l % tableSize : l;
    }
  }
};
