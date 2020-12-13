#pragma once

#include "ChainedHashNode.h"
#include "UniversalHash.h"
#include "VComparator.h"

// Hash map class template
template <typename K, typename V, size_t tableSize> class HashMap {
private:
  HashMap(const HashMap &other);
  const HashMap &operator=(const HashMap &other);
  HashNode<K, V> *table[tableSize];
  KeyHash<K> hashFunc;
  VComparator<K> comp;

public:
  HashMap() : table(), hashFunc(tableSize), comp() {}

  ~HashMap() {
    // destroy all buckets one by one
    for (size_t i = 0; i < tableSize; ++i) {
      HashNode<K, V> *entry = table[i];

      while (entry != NULL) {
        HashNode<K, V> *prev = entry;
        entry = entry->getNext();
        delete prev;
      }

      table[i] = NULL;
    }
  }

  bool search(const K &key, V &value) {
    unsigned int hashValue = hashFunc[key];
    HashNode<K, V> *entry = table[hashValue];
    unsigned int ccounter = 0;
    while (entry != NULL) {
      ccounter++;
      // std::cout << "hashkey: "<< hashValue << " value: " << entry->getValue()
      // <<std::endl;
      if (comp.compare(entry->getKey(), key)) {
        value = entry->getValue();
        // std::cout << "Number of tries: "<< ccounter <<std::endl;
        return true;
      }

      entry = entry->getNext();
    }
    // std::cout << "Number of tries: "<< ccounter <<std::endl;
    // std::cout << "UKNOWN KEY!"<< std::endl;
    return false;
  }

  void insert(const K &key, const V &value) {
    unsigned int hashValue = hashFunc[key];
    HashNode<K, V> *prev = NULL;
    HashNode<K, V> *entry = table[hashValue];
    // std::cout << "before while" << entry <<std::endl;
    while (entry != NULL && !comp.compare(entry->getKey(), key)) {
      prev = entry;
      entry = entry->getNext();
    }

    if (entry == NULL) {
      entry = new HashNode<K, V>(key, value);

      if (prev == NULL) {
        // insert as first bucket
        table[hashValue] = entry;

      } else {
        prev->setNext(entry);
      }

    } else {
      // just update the value
      entry->setValue(value);
    }
  }

  void remove(const K &key) {
    unsigned int hashValue = hashFunc[key];
    HashNode<K, V> *prev = NULL;
    HashNode<K, V> *entry = table[hashValue];

    while (entry != NULL && !comp.compare(entry->getKey(), key)) {
      prev = entry;
      entry = entry->getNext();
    }

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
};
