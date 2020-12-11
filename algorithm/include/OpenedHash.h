#pragma once
#include <math.h>
#include <random>
#include <string>

#include "UniversalHash.h"

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
  unsigned int c1 = 11;
  unsigned int c2 = 7;
  std::string hashType;

public:
  OpenKeyHash(size_t tableSize, std::string hashType)
      : tableSize(tableSize), uniHashFunc(tableSize), uniHashFuncAUX(tableSize),
        hashType(hashType){};

  unsigned int operator[](KeyAttempt<K> const &pairKA) const {
    if (hashType == "LINEAR") {
      return (uniHashFunc[pairKA.key] + pairKA.attempt) % tableSize;
    } else if (hashType == "QUADRATIC") {
      return (uniHashFunc[pairKA.key] + ((pairKA.attempt * c1) % prime) +
              ((pairKA.attempt * pairKA.attempt * c2) % prime)) %
             tableSize;
    } else if (hashType == "DOUBLE") {
      unsigned int auxHash1 = uniHashFunc[pairKA.key];
      // unsigned int auxHash2 = pairKA.key[0]; // ((auxHash1 << 1) >>
      // 2);///(auxHash1 % 2) + (auxHash1 / 2); //(auxHash1 >> 1);
      unsigned int l =
          auxHash1 + pairKA.attempt * (2 * (pairKA.key % 1071)); //* auxHash2;
      return (l >= tableSize) ? l % tableSize : l;
    } else {
      return (uniHashFunc[pairKA.key] + pairKA.attempt) % tableSize;
    }
  }
};

template <> class OpenKeyHash<std::string> {
private:
  size_t tableSize;
  KeyHash<std::string> uniHashFunc;
  KeyHash<std::string> uniHashFuncAUX;
  unsigned int prime = 97;
  unsigned int c1 = 11;
  unsigned int c2 = 7;
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
      return (uniHashFunc[pairKA.key] + ((pairKA.attempt * c1) % tableSize) +
              ((pairKA.attempt * pairKA.attempt * c2) % tableSize)) %
             tableSize;
    } else if (hashType == "DOUBLE") {
      unsigned int auxHash1 = uniHashFunc[pairKA.key];
      unsigned int auxHash2 = auxHash1 % 2 + auxHash1;
      unsigned int l = auxHash1 + pairKA.attempt * auxHash2;
      return (l >= tableSize) ? l % tableSize : l;
    } else {
      return (uniHashFunc[pairKA.key] + pairKA.attempt) % tableSize;
    }
  }
};
