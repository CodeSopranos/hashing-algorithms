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

public:
    // m - tableSize, n - numberOfElements m >= 2n
    CuckooHashMap(const size_t tableSize, const size_t numberOfElements):
            hashFunc_1(tableSize), hashFunc_2(tableSize), tableSize(tableSize), comp()

    {
        if (this->tableSize < 2*numberOfElements) {
            std::cerr<<"Error: m - tableSize, n - numberOfElements m < 2n!";
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
    bool insert(const K& key, const V& value) {
        auto* item = new OpenHashNode<K, V>(key, value);

        for (unsigned int i = 0; i < max_cuckoo; ++i) {
            unsigned int pos_1, pos_2;
            pos_1 = hashFunc_1[item->getKey()];
            pos_2 = hashFunc_2[item->getKey()];
            if (table_left[pos_1] == NULL) {
                table_left[pos_1] = item;
                return true;
            } else if (table_right[pos_2] == NULL) {
                table_right[pos_2] = item;
                return true;
            } else {
                std::swap(item, table_left[pos_1]);
                std::cout << "item:\n K, V = " << item->getKey() << ", " << item->getValue() << "\n";
            }
        }
        rehash();
        return insert_(item->getKey(), item->getValue());
    }
    bool insert_(const K& key, const V& value) {
        unsigned int key_left = hashFunc_1[key], key_right = hashFunc_2[key], attempt = 0;
        K move_key = key_left;
        OpenHashNode<K, V> item(key, value);
        OpenHashNode<K, V>* entry = table_left[move_key];
        bool condition = false;
        while (!condition) {
            attempt++;
            if (attempt >= max_cuckoo) {
                condition = true;
            }
            if (entry == NULL) {
                entry = new OpenHashNode<K, V>(move_key, value);
                if (move_key == key_left) {
                    table_left[move_key] = entry;
                } else if (move_key == key_right) {
                    table_right[move_key] = entry;
                }
                return 0;
            } else {
                number_of_collisions++;
                // swap
                V for_swap = item.getValue();
                entry->setValue(item.getValue());
                item.setValue(for_swap);

                if (move_key == key_left) {
                    key_left = hashFunc_1[item.getKey()];
                    key_right = hashFunc_2[item.getKey()];
                    move_key = key_right;
                    entry = table_right[move_key];
                } else if (move_key == key_right) {
                    key_left = hashFunc_1[item.getKey()];
                    key_right = hashFunc_2[item.getKey()];
                    move_key = key_left;
                    entry = table_left[move_key];
                } else {
                    std::cerr << "Error: CuckooHashMap::insert(), move_key != key_left and move_key != key_right\n";
                }
            }
        }
        if (attempt >= max_cuckoo) {
            rehash();
        }
    }
    bool search(const K& key, V& value) {
        OpenHashNode<K, V>* entry;
        if ((entry = table_left[ hashFunc_1[key] ]) != NULL) {
            if (comp.compare(entry->getKey(), key)) {
                value = entry->getValue();
                std::cout << "hash1: " << hashFunc_1[key] << " hash2: " << hashFunc_2[key] << std::endl;
                // std::cout << entry->getKey() <<
                return true;
            }
        } else if ((entry = table_right[ hashFunc_2[key] ]) != NULL) {
            if (comp.compare(entry->getKey(), key)) {
                value = entry->getValue();
                return true;
            }
        } else {
            std::cout << "Error: cannot search by key: " << key << std::endl;
            std::cout << "hash1: " << hashFunc_1[key] << " hash2: " << hashFunc_2[key] << std::endl;
            value = NULL;
            return false;
        }
    }
    void remove(const K& key) {
        OpenHashNode<K, V>* entry;
        unsigned long hash1 = hashFunc_1[key];
        unsigned long hash2 = hashFunc_2[key];

        if ((entry = table_left[ hash1 ]) != NULL) {
            if (comp.compare(entry->getKey(), key)) {
                table_left[ hash1 ] = NULL;
            }
        } else if ((entry = table_right[ hash2 ]) != NULL) {
            if (comp.compare(entry->getKey(), key)) {
                table_right[ hash2 ] = NULL;
            }
        } else {
            std::cerr << "Error: cannot remove by key: " << key << std::endl;
            std::cerr << "hash1: " << hash1 << " hash2: " << hash2 << std::endl;
        }
        // displayHash();
    }
    void rehash() {
        hashFunc_1 = KeyHash<K>(tableSize);
        hashFunc_2 = KeyHash<K>(tableSize);
        //displayHash();
        auto** table_copy = new OpenHashNode<K, V>*[2*tableSize]();
        for (int i = 0; i < tableSize; i++) {
            table_copy[i] = table_left[i];
        }
        for (int i = tableSize; i < 2*tableSize; i++) {
            table_copy[i] = table_right[i - tableSize];
        }
        delete table_left, table_right;
        table_left = new OpenHashNode<K, V>*[tableSize]();
        table_right = new OpenHashNode<K, V>*[tableSize]();
        for (int i = 0; i < 2*tableSize; i++) {
            if (table_copy[i] != NULL) {
                OpenHashNode<K, V>* entry = table_copy[i];
                insert(entry->getKey(), entry->getValue());
            }
        }
        std::cout << "\n\trehashed: \n";
        //displayHash();
    }
    void displayHash() {
        OpenHashNode <K, V> *entry = NULL;
        std::cout<<"\ntable1:     table2:\n";
        for (int i = 0; i < tableSize; i++) {
            entry = table_left[i];
            std::cout << i;
            if (entry != NULL) {
                std::cout << " -> " << entry->getKey() << "      ";
            } else {
                std::cout << "           ";
            }
            entry = table_right[i];
            std::cout << i;
            if (entry != NULL) {
                std::cout << " -> " << entry->getKey();
            }
            std::cout << std::endl;
        }
    }
};
