#pragma once

#include "OpenedHash.h"
#include "OpenedHashNode.h"
#include "UniversalHash.h"
#include "VComparator.h"

#define DELETED true

template <typename K, typename V> class OpenHashMap {
private:
  // OpenHashMap(const OpenHashMap &other);
  // const OpenHashMap &operator=(const OpenHashMap &other);
  size_t tableSize;
  OpenHashNode<K, V> **table;
  VComparator<K> comp;
  OpenKeyHash<K> hashFunc;
  unsigned int collisions = 0;

public:
  OpenHashMap(size_t tableSize, std::string hashType)
      : tableSize(tableSize), hashFunc(tableSize, hashType), comp() {
    table = new OpenHashNode<K, V> *[tableSize]();
  }

  ~OpenHashMap() {
    // destroy all buckets one by one
    for (size_t i = 0; i < tableSize; ++i) {
      OpenHashNode<K, V> *entry = table[i];
      delete entry;
      table[i] = NULL;
    }
  }

  bool insert(const K &key, const V &value) {
    KeyAttempt<K> pairKA = {key, 0};
    unsigned int hashValue = hashFunc[pairKA];
    while (table[hashValue] != NULL && table[hashValue]->getState() != DELETED) {
      if ( comp.compare(table[hashValue]->getKey(), key)){
        table[hashValue]->setValue(value);
        table[hashValue]->setState(!DELETED);
        return true;
      }
      pairKA.attempt++;
      hashValue = hashFunc[pairKA];
      if (pairKA.attempt == (tableSize+1)) {
        collisions += pairKA.attempt;
        return false;
      }

    }
    if (table[hashValue] == NULL) {
      table[hashValue] = new OpenHashNode<K, V>(key, value);
      collisions += pairKA.attempt;
      return true;
    } else if (table[hashValue]->getState() == DELETED) {
      collisions += pairKA.attempt;
      table[hashValue] = new OpenHashNode<K, V>(key, value);
      return true;
    } else {
      collisions += pairKA.attempt;
      table[hashValue]->setValue(value);
      return true;
    }
  }

  bool search(const K &key, V &value) {
    KeyAttempt<K> pairKA = {key, 0};
    unsigned int hashValue = hashFunc[pairKA];
    while (table[hashValue] != NULL) {
      if (table[hashValue]->getState() != DELETED) {
        if (comp.compare(table[hashValue]->getKey(), key)) {
          value = table[hashValue]->getValue();
          collisions += pairKA.attempt;
          return true;
        }
      }
      pairKA.attempt++;
      hashValue = hashFunc[pairKA];
      if (pairKA.attempt == tableSize) {
        collisions += pairKA.attempt;
        return false;
      }
    }
    return false;
  }

  void remove(const K &key) {
    unsigned int attempt = 0;
    KeyAttempt<K> pairKA = {key, attempt};
    unsigned int hashValue = hashFunc[pairKA];

    while (table[hashValue] != NULL && !comp.compare(table[hashValue]->getKey(), key)) {
      pairKA.attempt = ++attempt;
      hashValue = hashFunc[pairKA];
      if (attempt > tableSize) {
        collisions += attempt;
        return;
      }
    }

    if (table[hashValue] == NULL) {
      collisions += attempt;
      return;

    } else {
      collisions += attempt;
      table[hashValue]->setState(DELETED);
      return;
    }
  }

  void resetCollisions(){ collisions = 0; }

  unsigned int getNcollisions(){ return collisions; }

  void displayHash() {
    std::cout << std::endl;
    for (int i = 0; i < tableSize; i++) {
      std::cout << i;
      if (table[i]) {
        if (!table[i]->getState())
          std::cout << " -> " << table[i]->getKey() << std::endl;
        else
          std::cout << " -> NULL (DELETED)" << std::endl;
      } else
        std::cout << " -> NULL" << std::endl;
    }

    std::cout << std::endl;
  }
};
