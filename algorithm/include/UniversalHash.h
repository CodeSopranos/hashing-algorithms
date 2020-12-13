#pragma once
#include <math.h>
#include <random>
#include <string>

template <typename K> class KeyHash {
private:
  size_t tableSize;

public:
  KeyHash(size_t tableSize) : tableSize(tableSize) {}

  unsigned int operator[](const K &key) const {
    return reinterpret_cast<unsigned int>(key) % this->tableSize;
  }
};

template <> class KeyHash<int> {
private:
  size_t tableSize;
  unsigned int a, b;
  unsigned int prime = 101027;

public:
  KeyHash(size_t tableSize) {
    this->tableSize = tableSize;
    std::random_device randDev;
    std::mt19937 mers(randDev());
    std::uniform_int_distribution<int> a_uid(1, prime - 1);
    std::uniform_int_distribution<int> b_uid(0, prime - 1);
    this->a = a_uid(mers);
    this->b = b_uid(mers);
    //std::cout<<"a = " <<a <<", b ="<<b<< ", tablesize = " << tableSize <<std::endl;
  }
  unsigned int operator[](const int &key) const {
    // std::cout << this->a <<" "<< this->b << std::endl;
    // return ((this->a * key + this->b) % this->prime)  % this->tableSize;
    unsigned int l = a * key + b;
    if (l >= tableSize) {
      l = (l >= prime) ? l % prime : l;
      return (l >= tableSize) ? (l % tableSize) : l;
    } else {
      return l;
    }
  }
};

template <> class KeyHash<std::vector<int>> {
private:
  size_t tableSize;
  unsigned int a, prime = 101027;

public:
  KeyHash(size_t tableSize) {
    this->tableSize = tableSize;
    std::mt19937 mers(42);
    std::uniform_int_distribution<int> a_uid(1, prime - 1);
    this->a = a_uid(mers);
  }
  unsigned int operator[](const std::vector<int> &key) const {
    unsigned int hkey = 0;
    for (auto i = 0; i < key.size(); i++) {
      hkey = ((hkey * a) + key[i]);
      if (hkey > prime)
        hkey %= prime;
    }
    return hkey % tableSize;
  }
};


template <> class KeyHash<std::string> {
private:
  size_t tableSize;
  unsigned int a, prime = 5039;

public:
  KeyHash(size_t tableSize) {
    this->tableSize = tableSize;
    std::random_device randDev;
    std::mt19937 mers(randDev());
    std::uniform_int_distribution<int> a_uid(1, 127);
    this->a = a_uid(mers);
  }
  unsigned int operator[](const std::string key) const {
    unsigned int hkey = 0;
    for (auto i = 0; i < key.size(); ++i) {
      // hkey = ((hkey << 5) +  key[i]) ^ prime;
      hkey = a * hkey + key[i];
      hkey = (hkey >= prime) ? hkey % prime : hkey;
    }
    return (hkey >= tableSize) ? hkey % tableSize : hkey;
  }
};

template <typename K>
class KeyHashTest{
private:
    size_t tableSize;
public:
    KeyHashTest(size_t tableSize) : tableSize(tableSize) {}

    unsigned long operator[](const K& key) const
    {
        return reinterpret_cast<unsigned long>(key) % this->tableSize;
    }

};

template <>
class KeyHashTest<int>{
private:
    size_t tableSize;
    unsigned int a, b, p;
public:
    KeyHashTest(size_t tableSize_, unsigned int a_, unsigned int b_, unsigned int p_ = 101) :
            tableSize(tableSize_), a(a_), b(b_), p(p_)
    {
    }
    unsigned long operator[](const int& key) const
    {
        // std::cout << this->a <<" "<< this->b << std::endl;
        return ((this->a * key + this->b) % this->p )  % this->tableSize;
    }

};