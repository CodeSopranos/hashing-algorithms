#include "UniversalHash.h"
#include "primeNumbers.h"

template <typename K> class CuckooKeyHash {
private:
    size_t tableSize;
    KeyHash<K> uniHashFunc;
    unsigned int a;

public:
    CuckooKeyHash(size_t tableSize, unsigned int a)
    : tableSize(tableSize),
      uniHashFunc(tableSize),
      a(a){};

    unsigned int operator[](const K &key) const {
        unsigned int l = a * uniHashFunc[key];
        return (l >= tableSize) ? l % tableSize : l;
    }
};

template <> class CuckooKeyHash<int> {
private:
    size_t tableSize;
    KeyHash<int> uniHashFunc;
    unsigned int a;

public:
    CuckooKeyHash(size_t tableSize, unsigned int a)
            : tableSize(tableSize),
              uniHashFunc(tableSize),
              a(a){};

    unsigned int operator[](const int key) const {
        unsigned int l = a * uniHashFunc[key];
        return (l >= tableSize) ? l % tableSize : l;
    }
};

template <> class CuckooKeyHash<std::string> {
private:
    size_t tableSize;
    KeyHash<std::string> uniHashFunc;
    unsigned int a;

public:
    CuckooKeyHash(size_t tableSize, unsigned int a)
    : tableSize(tableSize),
      uniHashFunc(tableSize),
      a(a){

    };

    unsigned int operator[](const std::string key) const {
        unsigned int l = PRIME[a] * uniHashFunc[key];
        return (l >= tableSize) ? l % tableSize : l;
    }
};