#pragma once
#include <random>
#include <math.h>
#include <string>

template <typename K>
class KeyHash{
  private:
    size_t tableSize;
  public:
    KeyHash(size_t tableSize){
      this->tableSize = tableSize;
    }
    unsigned long operator[](const K& key) const
    {
      return reinterpret_cast<unsigned long>(key) % this->tableSize;
    }

};

template <>
class KeyHash<int>{
  private:
    size_t tableSize;
    unsigned int a, b;
    unsigned int p = 101027;
  public:
    KeyHash(size_t tableSize){
      this->tableSize = tableSize;
      std::random_device randDev;
      std::mt19937 mers(randDev());
      std::uniform_int_distribution<int> a_uid(1, this->p-1);
      std::uniform_int_distribution<int> b_uid(0, this->p-1);
      this->a = a_uid(mers);
      this->b = b_uid(mers);
      // std::cout<<"a " <<a <<" b "<<b<<std::endl;
    }
    unsigned long operator[](const int& key) const
    {
      // std::cout << this->a <<" "<< this->b << std::endl;
      return ((this->a * key + this->b) % this->p )  % this->tableSize;
    }

};


template <>
class KeyHash<std::vector<int>>{
  private:
    size_t tableSize;
    unsigned int a, p = 101027;
  public:
    KeyHash(size_t tableSize){
      this->tableSize = tableSize;
      std::mt19937 mers(42);
      std::uniform_int_distribution<int> a_uid(1, this->p-1);
      this->a = a_uid(mers);

    }
    unsigned long operator[](const std::vector<int>& key) const
    {
      unsigned long hkey = 0;
      for (auto i=0; i<key.size(); i++){
          hkey = ((hkey * this->a) + key[i]) % this->p;
      }
      return hkey % this->tableSize;
    }

};


template <>
class KeyHash<std::string>{
  private:
    size_t tableSize;
    unsigned int a, p = 3571;
  public:
    KeyHash(size_t tableSize){
      this->tableSize = tableSize;
      std::mt19937 mers(42);
      std::uniform_int_distribution<int> a_uid(1, this->p-1);
      this->a = a_uid(mers);

    }
    unsigned long operator[](const std::string key) const
    {
      unsigned long hkey = 0;
      for (auto i=0; i<key.size(); i++){
          hkey = ((hkey * this->a) + key[i]) % this->p;
      }
      return hkey % this->tableSize;
    }

};
