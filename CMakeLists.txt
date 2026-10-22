cmake_minimum_required(VERSION 3.15)
project(srulib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(srulib STATIC
   source/assets.cpp
   source/audio.cpp
   source/error.cpp
   source/file.cpp
   source/particles.cpp
   source/render.cpp
   source/text.cpp
   source/tween.cpp
)

find_package(raylib REQUIRED)
target_link_libraries(srulib PUBLIC raylib)

target_include_directories(srulib PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:include>)

install(TARGETS srulib
   EXPORT srulibTargets
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin)

install(EXPORT srulibTargets
   FILE srulibTargets.cmake
   DESTINATION lib/cmake/srulib)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

include(CMakePackageConfigHelpers)
configure_package_config_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/srulibConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/srulibConfig.cmake
   INSTALL_DESTINATION lib/cmake/srulib)

write_basic_package_version_file(
   ${CMAKE_CURRENT_BINARY_DIR}/srulibConfigVersion.cmake
   VERSION ${PROJECT_VERSION}
   COMPATIBILITY SameMajorVersion)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/srulibConfig.cmake
   ${CMAKE_CURRENT_BINARY_DIR}/srulibConfigVersion.cmake
   DESTINATION lib/cmake/srulib)
