#include <string>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> //
#include <random>
#include <algorithm>

std::vector<int> gen_rand_vec(int N){
   std::random_device rd;
   std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом

   #include <vector>


   std::vector<int> rand_vec(N);
   std::generate(rand_vec.begin(), rand_vec.end(), mersenne);


  return rand_vec;
 }
