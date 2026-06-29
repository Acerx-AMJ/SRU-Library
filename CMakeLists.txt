cmake_minimum_required(VERSION 3.10)
project(srulib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT TARGET raylib)
   find_package(raylib REQUIRED)
endif()

add_library(srulib STATIC
   source/assets.cpp
)

target_include_directories(srulib PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:include>
)
target_link_libraries(srulib PRIVATE raylib)
