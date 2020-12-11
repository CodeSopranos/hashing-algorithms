#include <array>
#include <cstring>
#include <string>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> //
#include <random>
#include <algorithm>
#include <functional>

int genRandomUid(unsigned int a,unsigned int b){
    std::random_device rd;
    std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом
    std::uniform_int_distribution<int> uid(a, b);
    return uid(mersenne);
}

std::vector<int> genRandVec(size_t N, unsigned int a, unsigned int b){

   std::vector<int> randVec(N);
   // std::generate(randVec.begin(), randVec.end(), genRandomUid(a,b));
   for (auto i = 0; i < randVec.size(); ++i){
      randVec[i] = genRandomUid(a, b);
  }

  return randVec;
 }


std::string genRandString(size_t stringLen){
     std::string resultStr;
     static std::random_device rd;
     static std::mt19937 mt(rd());
     static std::uniform_int_distribution<int> dist(-25, 25);
     for (int i = 0; i < stringLen; ++i) {
         resultStr += ('a' + dist(mt));
     }
     return resultStr;
 }

 std::vector<std::string> genRandStrings(size_t N){
      std::vector<std::string> randVec(N);
      static std::random_device rd;
      static std::mt19937 mt(rd());
      static std::uniform_int_distribution<int> dist(4, 20);
      for (auto i = 0; i < randVec.size(); ++i)
         randVec[i] = genRandString(dist(mt));
      return randVec;
  }


// auto random_generator() -> std::mt19937 {
//     // std::random_device dev;
//     auto constexpr seed_bytes = sizeof(typename std::mt19937::result_type) * std::mt19937::state_size;
//     auto constexpr seed_len = seed_bytes / sizeof(std::seed_seq::result_type);
//     auto seed = std::array<std::seed_seq::result_type, seed_len>();
//     std::generate_n(begin(seed), seed_len, std::ref(21));
//     auto seed_seq = std::seed_seq(begin(seed), end(seed));
//     return std::mt19937{seed_seq};
// }
//
// std::string genRandString(size_t stringLen){
//     static constexpr auto chars =
//         "0123456789"
//         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//         "abcdefghijklmnopqrstuvwxyz";
//     thread_local auto rng = random_generator();
//     auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
//     auto result = std::string(len, '\0');
//     std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; })
// }
