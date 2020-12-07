#pragma once
#include <list>
#include "VComparator.h"
#include "UniversalHash.h"
#include "LinkedHashNode.h"


// Hash map class template
template <typename K, typename V>
class HashMap
{
private:
    HashMap(const HashMap& other);
    const HashMap& operator=(const HashMap& other);
    // std::vector<HashNode<K, V>*> *table;
    KeyHash<K> hashFunc;
    HashNode<K, V>** table;  //  int *ptr;
    VComparator<K> comp;
    size_t tableSize;

public:
    HashMap(const size_t tableSize) :
        hashFunc(tableSize),
        comp()
    {
      this->tableSize = tableSize;
      table = new HashNode<K, V>*[tableSize]();
    }
    bool insert(const K& key, const V& value)
    {
        unsigned long hashValue = hashFunc[key];
        HashNode<K, V>* prev = NULL;
        HashNode<K, V>* entry = table[hashValue];
        // std::cout << "before while" << &entry <<std::endl;
        while (entry != NULL && !comp.compare(entry->getKey(), key)) {
            // std::cout << "entry != NULL" << std::endl;
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            // std::cout << "entry == NULL" << std::endl;
            entry = new HashNode<K, V>(key, value);

            if (prev == NULL) {
                // insert as first bucket
                table[hashValue] = entry;
                return true;

            }
            else {
                prev->setNext(entry);
                return true;
            }

        }
        else {
            // just update the value
            entry->setValue(value);
            return true;
        }
        return false;
    }
    bool search(const K& key, V& value)
    {
    unsigned long hashValue = hashFunc[key];
    HashNode<K, V>* entry = table[hashValue];
    unsigned int ccounter = 0;
    while (entry != NULL) {
        ccounter++;
        // std::cout << "hashkey: "<< hashValue << " value: " << entry->getValue() <<std::endl;
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

void remove(const K& key)
{
      unsigned long hashValue = hashFunc[key];
      HashNode<K, V>* prev = NULL;
      HashNode<K, V>* entry = table[hashValue];

      while (entry != NULL && !comp.compare(entry->getKey(), key)) {
          prev = entry;
          entry = entry->getNext();
      }

      if (entry == NULL) {
          // key not found
          return;

      }
      else {
          if (prev == NULL) {
              // remove first bucket of the list
              table[hashValue] = entry->getNext();

          }
          else {
              prev->setNext(entry->getNext());
          }

          delete entry;
      }
  }
    void displayHash() {
    HashNode<K,V>* entry = NULL;
    for (int i = 0; i < tableSize; i++) {
      entry = table[i];
      std::cout << i;
      while (entry != NULL) {
          std::cout << " -> " << entry->getKey();
          entry = entry->getNext();
      }
      std::cout << std::endl;
    }
  }

};
