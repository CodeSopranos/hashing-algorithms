#pragma once

#include "OpenedHashNode.h"
#include "UniversalHash.h"
#include "VComparator.h"

const int DELETED = -1;

template <typename K, typename V, size_t tableSize> class OpenHashMap {
private:
  OpenHashMap(const OpenHashMap &other);
  const OpenHashMap &operator=(const OpenHashMap &other);
  OpenHashNode<K, V> *table[tableSize];
  VComparator<K> comp;
  KeyHash<K> hashFunc;

public:
  OpenHashMap() : table(), hashFunc(tableSize), comp() {}

  ~OpenHashMap() {
    // destroy all buckets one by one
    for (size_t i = 0; i < tableSize; ++i) {
      OpenHashNode<K, V> *entry = table[i];
      delete entry;
      table[i] = NULL;
    }
  }

  bool insert(const K &key, const V &value) {
    unsigned int attempt = 0;
    unsigned int hashValue = hashFunc[key];
    OpenHashNode<K, V> *entry = table[hashValue];
    // std::cout <<"\nkey: " << key << " hash: " << hashValue << std::endl;
    while (entry != NULL && entry->getKey() != DELETED) {
      attempt++;
      // std::cout << attempt << " ";
      hashValue = (hashFunc[key] + attempt) % tableSize;
      entry = table[hashValue];
      if (attempt >= tableSize - 1) {
        // std::cout << "Opened Hash Table is full!";
        return false;
      }
    }
    if (entry == NULL) {
      // std::cout << "entry == NULL"<< std::endl;
      entry = new OpenHashNode<K, V>(key, value);
      table[hashValue] = entry;
      return true;
    } else if (entry->getKey() == DELETED) {
      // std::cout << "entry == DELETED"<< std::endl;
      entry->setKey(key);
      entry->setValue(value);
      return true;
    } else {
      // std::cout << "entry set new value" << std::endl;
      entry->setValue(value);
      return true;
    }
  }

  bool search(const K &key, V &value) {
    unsigned int attempt = 0;
    unsigned int hashValue = hashFunc[key];
    OpenHashNode<K, V> *entry = table[hashValue];
    while (entry != NULL) {
      // std::cout << "hashkey: "<< hashValue << " value: " << entry->getValue()
      // <<std::endl;
      if (comp.compare(entry->getKey(), key)) {
        value = entry->getValue();
        return true;
      }
      attempt++;
      hashValue = (hashFunc[key] + attempt) % tableSize;
      entry = table[hashValue];
      if (attempt >= tableSize - 1) {
        // std::cout << "Opened Hash Table is full!";
        // std::cout << "Number of tries: "<< attempt <<std::endl;
        // std::cout << "UKNOWN KEY!"<< std::endl;
        return false;
      }
    }
    return false;
  }

  void remove(const K &key) {
    unsigned int attempt = 0;
    unsigned int hashValue = hashFunc[key];
    OpenHashNode<K, V> *entry = table[hashValue];

    while (entry != NULL && !comp.compare(entry->getKey(), key)) {
      attempt++;
      hashValue = (hashFunc[key] + attempt) % tableSize;
      entry = table[hashValue];
      if (attempt >= tableSize - 1) {
        // std::cout << "Opened Hash Table is full!";
        // std::cout << "Number of tries: "<< attempt <<std::endl;
        // std::cout << "UKNOWN KEY!"<< std::endl;
        return;
      }
    }

    if (entry == NULL) {
      // std::cout << "Number of tries: "<< attempt <<std::endl;
      // std::cout << "UKNOWN KEY!"<< std::endl;
      return;

    } else {
      entry->setKey(DELETED);
      entry->setValue(DELETED);
    }
  }
};
