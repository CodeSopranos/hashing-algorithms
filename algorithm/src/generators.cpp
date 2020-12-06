#include <string>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> //
#include <random>
#include <algorithm>



int genRandomUid(){
    std::random_device rd;
    std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом
    std::uniform_int_distribution<int> uid(0, 1000);
    return uid(mersenne);
}

std::vector<int> genRandVec(int N){

   std::vector<int> randVec(N);
   std::generate(randVec.begin(), randVec.end(), genRandomUid);


  return randVec;
 }
