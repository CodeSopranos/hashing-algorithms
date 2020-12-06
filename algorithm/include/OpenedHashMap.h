#pragma once

#include "UniversalHash.h"
#include "OpenedHashNode.h"

const int DELETED = -1;

template <typename K, typename V, size_t tableSize>
class OpenHashMap
{
private:
    OpenHashMap(const OpenHashMap& other);
    const OpenHashMap& operator=(const OpenHashMap& other);
    OpenHashNode<K, V>* table[tableSize];
    KeyHash<K> hashFunc;
    VComparator<K> comp;

public:
   OpenHashMap():
        table(),
        hashFunc(tableSize),
        comp()
    {
    }

    ~OpenHashMap()
    {
        // destroy all buckets one by one
        for (size_t i = 0; i < tableSize; ++i) {
            HashNode<K, V>* entry = table[i];
            delete entry;
            table[i] = NULL;
        }
    }

    void insert(const K& key, const V& value)
    {
        unsigned int attempt = 0;
        unsigned long hashValue = hashFunc[key];
        HashNode<K, V>* entry = table[hashValue];
        while (entry != NULL) {
            attempt++;
            hashValue = (hashFunc[key] + attempt) % tableSize;
            entry = table[hashValue];
            if (attempt >= tableSize-1)
            {
              std::cout << "Opend Hash Table is full!";
              return;

            }
        }
        if (entry == NULL) {
            entry = new HashNode<K, V>(key, value);
        }
        else {
            entry->setValue(value);
        }
    }

    bool search(const K& key, V& value)
    {
        unsigned int attempt = 0;
        unsigned long hashValue = hashFunc[key];
        HashNode<K, V>* entry = table[hashValue];
        while (entry != NULL) {
            // std::cout << "hashkey: "<< hashValue << " value: " << entry->getValue() <<std::endl;
            if (comp.compare(entry->getKey(), key)) {
                value = entry->getValue();
                std::cout << "Number of tries: "<< ccounter <<std::endl;
                return true;
            }
            attempt++;
            hashValue = (hashFunc[key] + attempt) % tableSize;
            entry = table[hashValue];
            if (attempt >= tableSize-1)
            {
              std::cout << "Opend Hash Table is full!";
              std::cout << "Number of tries: "<< attempt <<std::endl;
              std::cout << "UKNOWN KEY!"<< std::endl;
              return false;

            }
        return false;
    }
  }


    void remove(const K& key)
    {
        unsigned int attempt = 0;
        unsigned long hashValue = hashFunc[key];
        HashNode<K, V>* entry = table[hashValue];

        while (entry != NULL && !comp.compare(entry->getKey(), key)) {
            attempt++;
            hashValue = (hashFunc[key] + attempt) % tableSize;
            entry = table[hashValue];
            if (attempt >= tableSize-1)
            {
              std::cout << "Opend Hash Table is full!";
              std::cout << "Number of tries: "<< attempt <<std::endl;
              std::cout << "UKNOWN KEY!"<< std::endl;
              return;

            }
        }

        if (entry == NULL) {
            std::cout << "Number of tries: "<< attempt <<std::endl;
            std::cout << "UKNOWN KEY!"<< std::endl;
            return;

        }
        else {
            entry -> setValue(DELETED);
        }
    }
};
