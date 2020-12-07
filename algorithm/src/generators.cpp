#include <string>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> //
#include <random>
#include <algorithm>


int genRandomUid(unsigned int a,unsigned int b){
    std::random_device rd;
    std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом
    std::uniform_int_distribution<int> uid(a, b);
    return uid(mersenne);
}

std::vector<int> genRandVec(int N, unsigned int a, unsigned int b){

   std::vector<int> randVec(N);
   // std::generate(randVec.begin(), randVec.end(), genRandomUid(a,b));
   for (auto i = 0; i < randVec.size(); ++i){
      randVec[i] = genRandomUid(a, b);
  }

  return randVec;
 }
