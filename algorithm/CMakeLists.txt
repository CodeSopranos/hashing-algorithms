cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(hashing-algorithm)

file(GLOB SOURCES "src/*.cpp")

add_executable(hashing_algorithm ${SOURCES})
target_include_directories(hashing_algorithm PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_property(TARGET hashing_algorithm PROPERTY CXX_STANDARD 11)