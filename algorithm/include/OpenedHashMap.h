#pragma once

#include "OpenedHash.h"
#include "OpenedHashNode.h"
#include "UniversalHash.h"
#include "VComparator.h"

#define DELETED true

template <typename K, typename V> class OpenHashMap {
private:
  OpenHashMap(const OpenHashMap &other);
  const OpenHashMap &operator=(const OpenHashMap &other);
  size_t tableSize;
  OpenHashNode<K, V> **table;
  VComparator<K> comp;
  OpenKeyHash<K> hashFunc;

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
    unsigned int attempt = 0;
    KeyAttempt<K> pairKA = {key, attempt};
    unsigned int hashValue = hashFunc[pairKA];
    OpenHashNode<K, V> *entry = table[hashValue];
    // std::cout <<"\nkey: " << key << " hash: " << hashValue << std::endl;
    while (entry != NULL && entry->getState() != DELETED) {
      attempt++;
      // std::cout << attempt << " ";
      pairKA.attempt = attempt;
      hashValue = hashFunc[pairKA];
      entry = table[hashValue];
      if (attempt > tableSize) {
        // std::cout << "Opened Hash Table is full! " << value << std::endl;
        return false;
      }
    }
    if (entry == NULL) {
      // std::cout << "entry == NULL"<< std::endl;
      // std::cout << "entry set " << value << std::endl;
      table[hashValue] = new OpenHashNode<K, V>(key, value);
      return true;
    } else if (entry->getState() == DELETED) {
      // std::cout << "entry == DELETED"<< std::endl;
      entry->setKey(key);
      entry->setValue(value);
      entry->setState(!DELETED);
      return true;
    } else {
      // std::cout << "entry set new value " << value << std::endl;
      entry->setValue(value);
      return true;
    }
  }

  bool search(const K &key, V &value) {
    unsigned int attempt = 0;
    KeyAttempt<K> pairKA = {key, attempt};
    unsigned int hashValue = hashFunc[pairKA];
    OpenHashNode<K, V> *entry = table[hashValue];
    while (entry != NULL) {
      // std::cout << "hashkey: "<< hashValue << " value: " << entry->getValue()
      // <<std::endl;
      if (entry->getState() != DELETED) {
        if (comp.compare(entry->getKey(), key)) {
          value = entry->getValue();
          return true;
        }
      }
      pairKA.attempt = ++attempt;
      hashValue = hashFunc[pairKA];
      entry = table[hashValue];
      if (attempt > tableSize) {
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
    KeyAttempt<K> pairKA = {key, attempt};
    unsigned int hashValue = hashFunc[pairKA];
    OpenHashNode<K, V> *entry = table[hashValue];

    while (entry != NULL && !comp.compare(entry->getKey(), key)) {
      attempt++;
      pairKA.attempt = attempt;
      hashValue = hashFunc[pairKA]; //(hashFunc[key] + attempt) % tableSize;
      entry = table[hashValue];
      if (attempt > tableSize - 1) {
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
      entry->setState(DELETED);
      entry->setState(DELETED);
    }
  }

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
