cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(LevelGen
  LANGUAGES CXX
  VERSION 0.1.0
)

add_executable(LevelGen
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/DrawLevel.cpp
)

target_compile_features(LevelGen PRIVATE cxx_std_20)

if(MSVC)
  target_compile_options(LevelGen PRIVATE /W4)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(LevelGen PRIVATE -Wall -Wextra -pedantic)
endif()
