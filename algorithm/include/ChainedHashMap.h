#pragma once
#include "ChainedHashNode.h"
#include "UniversalHash.h"
#include "VComparator.h"
#include <list>

// Hash map class template
template <typename K, typename V> class HashMap {
private:
  // HashMap(const HashMap &other);
  // const HashMap &operator=(const HashMap &other);
  // std::vector<HashNode<K, V>*> *table;
  KeyHash<K> hashFunc;
  HashNode<K, V> **table; //  int *ptr;
  VComparator<K> comp;
  size_t tableSize;
  unsigned int collisions = 0;

public:
  HashMap(const size_t tableSize) : hashFunc(tableSize), comp() {
    this->tableSize = tableSize;
    table = new HashNode<K, V> *[tableSize]();
  }
  
  bool insert(const K &key, const V &value) {
    unsigned int attempt = 0;
    unsigned int hashValue = hashFunc[key];
    HashNode<K, V> *prev = NULL;
    HashNode<K, V> *entry = table[hashValue];
    while (entry != NULL && !comp.compare(entry->getKey(), key)) {
      ++attempt;
      prev = entry;
      entry = entry->getNext();
    }
    collisions += attempt;

    if (entry == NULL) {
      entry = new HashNode<K, V>(key, value);

      if (prev == NULL) {
        table[hashValue] = entry;
        return true;

      } else {
        prev->setNext(entry);
        return true;
      }

    } else {
      entry->setValue(value);
      return true;
    }
    return false;
  }
  bool search(const K &key, V &value) {
    unsigned int hashValue = hashFunc[key];
    HashNode<K, V> *entry = table[hashValue];
    unsigned int attempt = 0;
    while (entry != NULL) {
      ++attempt;
      if (comp.compare(entry->getKey(), key)) {
        collisions += attempt;
        value = entry->getValue();
        return true;
      }
      entry = entry->getNext();
    }
    collisions += attempt;
    return false;
  }

  void remove(const K &key) {
    unsigned int attempt = 0;
    unsigned int hashValue = hashFunc[key];
    HashNode<K, V> *prev = NULL;
    HashNode<K, V> *entry = table[hashValue];

    while (entry != NULL && !comp.compare(entry->getKey(), key)) {
      ++attempt;
      prev = entry;
      entry = entry->getNext();
    }
    collisions += attempt;

    if (entry == NULL) {
      // key not found
      return;

    } else {
      if (prev == NULL) {
        // remove first bucket of the list
        table[hashValue] = entry->getNext();

      } else {
        prev->setNext(entry->getNext());
      }
      delete entry;
    }
  }

  void resetCollisions(){ collisions = 0; }

  unsigned int getNcollisions(){ return collisions; }

  //   void displayHash() {
  //   HashNode<K,V>* entry = NULL;
  //   for (int i = 0; i < tableSize; i++) {
  //     entry = table[i];
  //     std::cout << i;
  //     while (entry != NULL) {
  //         std::cout << " -> " << entry->getKey();
  //         entry = entry->getNext();
  //     }
  //     std::cout << std::endl;
  //   }
  // }
};
