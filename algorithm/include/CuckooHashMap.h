#include "UniversalHash.h"
#include "OpenedHashNode.h"
#include <math.h>
#include <iostream>
#include "VComparator.h"

// m - tableSize
template <typename K, typename V>
class CuckooHashMap
{
private:
    OpenHashNode<K, V>* item_problem;
    CuckooHashMap(const CuckooHashMap &item);
    const CuckooHashMap& operator=(const CuckooHashMap& other);
    OpenHashNode<K, V>** table_left; //[tableSize];
    OpenHashNode<K, V>** table_right; //[tableSize];
    unsigned int max_cuckoo; //= 6*log2(numberOfElements);
    unsigned int number_of_collisions = 0;
    KeyHash<K> hashFunc_1; // = KeyHash<K>(tableSize, seed);
    KeyHash<K> hashFunc_2; // = KeyHash<K>(tableSize, seed + 1);
    size_t tableSize;
    VComparator<K> comp;
    bool verbose = 0;
    int numberOfInserts = 0, numberOfSearch = 0, numberOfRemove = 0, numberOfRehash = 0;
public:
    // m - tableSize, n - numberOfElements m >= 2n
    CuckooHashMap(const size_t tableSize, const size_t numberOfElements):
            hashFunc_1(tableSize), hashFunc_2(tableSize), tableSize(tableSize), comp()

    {
        if (this->tableSize < 2*numberOfElements) {
            std::cerr<<"\nError: m - tableSize, n - numberOfElements m < 2n!";
        }
        max_cuckoo = 6*log2(numberOfElements);
        table_left = new OpenHashNode<K, V>*[tableSize]();
        table_right = new OpenHashNode<K, V>*[tableSize]();
    }

    ~CuckooHashMap()
    {
        // destroy all buckets one by one
        for (size_t i = 0; i < tableSize; ++i) {
            OpenHashNode<K, V>* entry_left = table_left[i];
            OpenHashNode<K, V>* entry_right = table_right[i];
            delete entry_left, entry_right;
            table_left[i] = NULL;
            table_right[i] = NULL;
        }
    }

    void swap(OpenHashNode<K, V>* item, OpenHashNode<K, V>* item_) {
        K key = item->getKey(), key_ = item_->getKey(), temp_k;
        V value = item->getValue(), value_ = item_->getValue(), temp_v;
        temp_k = key;
        temp_v = value;
        key = key_;
        value = value_;
        key_ = temp_k;
        value_ = temp_v;
        item->setKey(key);
        item->setValue(value);
        item_->setKey(key_);
        item_->setValue(value_);
    }
    int getNumberOfInserts() {
        std::cout << "num ins: " << numberOfInserts << ", rehash: " << numberOfRehash << std::endl;
        return numberOfInserts;
    };
    bool insert(const K& key, const V& value) {
        numberOfInserts++;
        auto* item = new OpenHashNode<K, V>(key, value);

        for (unsigned int i = 0; i < max_cuckoo; ++i) {
            unsigned int pos_1, pos_2;
            pos_1 = hashFunc_1[item->getKey()];
            pos_2 = hashFunc_2[item->getKey()];
            if ((table_left[pos_1] == NULL) || ((table_left[pos_1]->getKey() == key) && (table_left[pos_1]->getValue() == value))) {
                table_left[pos_1] = item;
                return true;
            } else if ((table_right[pos_2] == NULL) || ((table_right[pos_2]->getKey() == key) && (table_right[pos_2]->getValue() == value))) {
                table_right[pos_2] = item;
                return true;
            }
            //if (pos_1 % 3 == 0){
            item_problem = table_left[pos_1];
            swap(item, table_left[pos_1]);
            //} else {
            //    std::swap(item, table_right[pos_2]);
            //}
            if (verbose) {
                std::cout << "item:\n K, V = " << item->getKey() << ", " << item->getValue() << "\n";
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
        //std::cout << "Error: cannot search by key: " << key << std::endl;
        //std::cout << "hash1: " << hashFunc_1[key] << " hash2: " << hashFunc_2[key] << std::endl;
        //value = NULL;
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
        // displayHash();
    }
    void rehash() {
        numberOfRehash++;
        hashFunc_1 = KeyHash<K>(tableSize);
        hashFunc_2 = KeyHash<K>(tableSize);
        //displayHash();
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
            //displayHash();
        }
        delete[] table_copy_left, table_copy_right;
    }
    void displayHash() {
        OpenHashNode <K, V> *entry = NULL;
        if (verbose) {
            std::cout << "\ntable1:                 table2:\n";
        }
        for (int i = 0; i < tableSize; i++) {
            entry = table_left[i];
            std::cout << i;
            if (verbose) {
                if (entry != NULL) {
                    std::cout << " -> (" << entry->getKey() << ", " << entry->getValue() << ")    " ;
                } else {
                    std::cout << "                       ";
                }
            }
            entry = table_right[i];
            if (verbose) {
                std::cout << i;
                if (entry != NULL) {
                    std::cout << " -> (" << entry->getKey() << ", " << entry->getValue() << ")";
                }
                std::cout << std::endl;
            }
        }
    }
};
