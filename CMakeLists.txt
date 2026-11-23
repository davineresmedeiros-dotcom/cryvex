cmake_minimum_required(VERSION 3.21)

project(Cryvex VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT ANDROID)
    message(FATAL_ERROR "Cryvex por enquanto só compila para Android (use o toolchain do NDK).")
endif()

add_library(cryvex SHARED src/main.cpp)

target_include_directories(cryvex PUBLIC include)
target_compile_options(cryvex PRIVATE -Wall -Wextra -fvisibility=hidden)
target_link_libraries(cryvex PRIVATE log)
