#pragma once
#include <random>
#include <math.h>
#include <string>

#include "UniversalHash.h"


template<typename T>
struct KeyAttempt
{
  const T& key;
  unsigned int attempt;
};


template <typename K>
class OpenKeyHash
{
  private:
    size_t tableSize;
    KeyHash<K> uniHashFunc;
    KeyHash<K> uniHashFuncAUX;
    unsigned int p = 101027;
    std::string hashType;
  public:
    OpenKeyHash(size_t tableSize, std::string hashType) :
      tableSize(tableSize),
      uniHashFunc(tableSize),
      uniHashFuncAUX(tableSize),
      hashType(hashType){};

    unsigned long operator[](KeyAttempt<K> const& pairKA) const
    {
      if (hashType == "LINEAR"){
        return (uniHashFunc[pairKA.key] + pairKA.attempt) % tableSize;
      }
      else if (hashType == "QUADRATIC")
      {
        return (uniHashFunc[pairKA.key] +
               ((pairKA.attempt * pairKA.key)  % p) +
               ((pairKA.attempt * pairKA.attempt * pairKA.key)  % p)) % tableSize;
      }
      else{
        return (uniHashFunc[pairKA.key] + pairKA.attempt) % tableSize;
      }
    }
};
