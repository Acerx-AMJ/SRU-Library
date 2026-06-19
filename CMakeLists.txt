cmake_minimum_required(VERSION 3.10)
project(srulib VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include Raylib
include(FetchContent)

FetchContent_Declare(
   raylib
   GIT_REPOSITORY https://github.com/raysan5/raylib.git
   GIT_TAG 5.5
   GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

# Do shit
add_library(srulib STATIC
      
)

target_include_directories(srulib
   PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
)
target_link_libraries(srulib PUBLIC raylib)

if(WIN32)
   target_link_libraries(srulib PUBLIC winmm)
elseif(APPLE)
   target_link_libraries(srulib PUBLIC
      "-framework OpenGL"
      "-framework Cocoa"
      "-framework IOKit"
      "-framework CoreAudio"
      "-framework CoreVideo"
   )
elseif(UNIX)
   target_link_libraries(srulib PUBLIC GL m pthread dl)
endif()

# Install
include(GNUInstallDirs)

install(TARGETS srulib
   EXPORT srulibTargets
   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Package
include(CMakePackageConfigHelpers)

install(EXPORT srulibTargets
   FILE srulibTargets.cmake
   NAMESPACE srulib::
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/srulib
)

configure_package_config_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/cmake/srulibConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/srulibConfig.cmake
   INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/srulib
)

write_basic_package_version_file(
   ${CMAKE_CURRENT_BINARY_DIR}/srulibConfigVersion.cmake
   VERSION ${PROJECT_VERSION}
   COMPATIBILITY SameMajorVersion
)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/srulibConfig.cmake
   ${CMAKE_CURRENT_BINARY_DIR}/srulibConfigVersion.cmake
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/srulib
)
