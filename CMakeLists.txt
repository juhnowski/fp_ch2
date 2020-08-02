 cmake_minimum_required(VERSION 2.8.12)
 project(MD5Encrypter)

 add_definitions("-std=c++17")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(fp_ch2 main.cpp)
 target_link_libraries(fp_ch2 ${CONAN_LIBS})