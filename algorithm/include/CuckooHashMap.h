#pragma once
#include <iostream>
#include <math.h>

#include "utils.h"
#include "CuckooHash.h"
#include "OpenedHashNode.h"
#include "VComparator.h"


// m - tableSize
template <typename K, typename V>
class CuckooHashMap
{
private:
    // CuckooHashMap(const CuckooHashMap &item);
    // const CuckooHashMap& operator=(const CuckooHashMap& other);
    OpenHashNode<K, V>** table_left;
    OpenHashNode<K, V>** table_right;
    unsigned int max_cuckoo;
    unsigned int collisions = 0;
    CuckooKeyHash<K> hashFunc_1;
    CuckooKeyHash<K> hashFunc_2;
    size_t tableSize;
    VComparator<K> comp;
    bool verbose = 0;
    int numberOfInserts = 0, numberOfSearch = 0, numberOfRemove = 0, numberOfRehash = 0;
public:
    // m - tableSize, n - numberOfElements m >= 2n
    CuckooHashMap(const size_t tableSize, const size_t numberOfElements):
            hashFunc_1(tableSize),
            hashFunc_2(tableSize),
            tableSize(tableSize),
            comp()

    {
        if ((this->tableSize < 2*numberOfElements) && (verbose)) {
            std::cerr<<"\nWarning: m - tableSize, n - numberOfElements m < 2n!";
        }
        max_cuckoo = 6*log2(numberOfElements);
        table_left = new OpenHashNode<K, V>*[tableSize]();
        table_right = new OpenHashNode<K, V>*[tableSize]();
    }

    void swap(OpenHashNode<K, V>* item, OpenHashNode<K, V>* item_) {
        OpenHashNode<K, V> temp_item = *item;
        *item = *item_;
        *item_ = temp_item;
    }

    bool insert(const K& key, const V& value) {
        numberOfInserts++;
        auto* item = new OpenHashNode<K, V>(key, value);

        for (auto i = 0; i < max_cuckoo; ++i) {
            unsigned int pos_1, pos_2;
            pos_1 = hashFunc_1[item->getKey()];
            pos_2 = hashFunc_2[item->getKey()];
            if ((table_left[pos_1] == NULL) ||
                (comp.compare(table_left[pos_1]->getKey(), item->getKey()))) {
                table_left[pos_1] = item;
                return true;
            }
            if ((table_right[pos_2] == NULL) ||
            (comp.compare(table_right[pos_2]->getKey(), item->getKey()))) {
                table_right[pos_2] = item;
                return true;
            }
            if (verbose) {
                //std::cout << "item:\n K, V = " << item->getKey() << ", " << item->getValue() << ", table K, V = " << table_left[pos_1]->getKey() << ", " << table_left[pos_1]->getValue() << "\n";
            }
            swap(item, table_left[pos_1]);
            collisions++;

            if (verbose) {
                //std::cout << "item:\n K, V = " << item->getKey() << ", " << item->getValue() << ", table K, V = " << table_left[pos_1]->getKey() << ", " << table_left[pos_1]->getValue() << "\n";
                //std::cout << "pos_1: " << pos_1 << ", pos_2: " << pos_2 << std::endl;
            }
        }
        rehash();
        return insert(item->getKey(), item->getValue());
    }

    bool search(const K& key, V& value) {
        numberOfSearch++;
        if (verbose) {
            std::cout << "\nsearch: key [" << key << "] ";
        }
        OpenHashNode<K, V>* entry;
        if ((entry = table_left[ hashFunc_1[key] ]) != NULL) {
            if (comp.compare(entry->getKey(), key)) {
                value = entry->getValue();
                if (verbose) {
                    std::cout << "key equal: hash1: " << hashFunc_1[key] << " hash2: " << hashFunc_2[key] << std::endl;
                }
                // std::cout << entry->getKey() <<
                return true;
            }
            if (verbose) {
                std::cout << "not key equal: hash1: " << hashFunc_1[key] << " hash2: " << hashFunc_2[key] << std::endl;
            }
        }
        if ((entry = table_right[ hashFunc_2[key] ]) != NULL) {
            if (comp.compare(entry->getKey(), key)) {
                value = entry->getValue();
                if (verbose) {
                    std::cout << "search(key equal): hash1: " << hashFunc_1[key] << " hash2: " << hashFunc_2[key]
                              << std::endl;
                }
                return true;
            }
            if (verbose) {
                std::cout << "search(not key equal): hash1: " << hashFunc_1[key] << " hash2: " << hashFunc_2[key]
                          << std::endl;
            }
        }

        return false;
    }


    void remove(const K& key) {
        numberOfRemove++;
        if (verbose) {
            std::cout << "\ndelete: key [" << key << "] ";
        }
        OpenHashNode<K, V>* entry;
        unsigned long hash1 = hashFunc_1[key];
        unsigned long hash2 = hashFunc_2[key];

        if ((entry = table_left[ hash1 ]) != NULL) {
            if (comp.compare(entry->getKey(), key)) {
                table_left[ hash1 ] = NULL;
            }
        }
        if ((entry = table_right[ hash2 ]) != NULL) {
            if (comp.compare(entry->getKey(), key)) {
                table_right[ hash2 ] = NULL;
            }
        }
        if (verbose) {
            std::cerr << "Error: cannot remove by key: " << key << std::endl;
            std::cerr << "hash1: " << hash1 << " hash2: " << hash2 << std::endl;
        }
    }
    void rehash() {
        numberOfRehash++;
        hashFunc_1 = CuckooKeyHash<K>(tableSize);
        hashFunc_2 = CuckooKeyHash<K>(tableSize);
        auto** table_copy_left = new OpenHashNode<K, V>*[tableSize]();
        auto** table_copy_right = new OpenHashNode<K, V>*[tableSize]();

        for (int i = 0; i < tableSize; i++) {
            table_copy_left[i] = table_left[i];
        }
        for (int i = 0; i < tableSize; i++) {
            table_copy_right[i] = table_right[i];
        }

        delete table_left, table_right;
        table_left = new OpenHashNode<K, V>*[tableSize]();
        table_right = new OpenHashNode<K, V>*[tableSize]();
        for (int i = 0; i < tableSize; i++) {
            if (table_copy_left[i] != NULL) {
                OpenHashNode<K, V>* entry = table_copy_left[i];
                insert(entry->getKey(), entry->getValue());
            }
        }
        for (int i = 0; i < tableSize; i++) {
            if (table_copy_right[i] != NULL) {
                OpenHashNode<K, V>* entry = table_copy_right[i];
                insert(entry->getKey(), entry->getValue());
            }
        }
        if (verbose) {
            std::cout << "\n\trehashed: \n";
        }
        delete[] table_copy_left, table_copy_right;
    }

    unsigned int getNcollisions(){ return collisions; }

    void resetCollisions(){ collisions = 0; }

    // unsigned int getNumberOfRemoves() {
    //     return numberOfRemove;
    // }
    // unsigned int getNumberOfSearches() {
    //     return numberOfSearch;
    // }
    // unsigned int getNumberOfInserts() {
    //     return numberOfInserts;
    // }

    // void resetCounters() {
    //     numberOfRemove = 0;
    //     numberOfSearch = 0;
    //     numberOfInserts = 0;
    // }
    // void displayHash() {
    //     OpenHashNode <K, V> *entry = NULL;
    //     if (verbose) {
    //         std::cout << "\ntable1:                 table2:\n";
    //     }
    //     for (int i = 0; i < tableSize; i++) {
    //         entry = table_left[i];
    //         std::cout << i;
    //         if (verbose) {
    //             if (entry != NULL) {
    //                 std::cout << " -> (" << entry->getKey() << ", " << entry->getValue() << ")    " ;
    //             } else {
    //                 std::cout << "                       ";
    //             }
    //         }
    //         entry = table_right[i];
    //         if (verbose) {
    //             std::cout << i;
    //             if (entry != NULL) {
    //                 std::cout << " -> (" << entry->getKey() << ", " << entry->getValue() << ")";
    //             }
    //             std::cout << std::endl;
    //         }
    //     }
    // }
};
