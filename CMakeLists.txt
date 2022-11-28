cmake_minimum_required(VERSION 3.19)
include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY https://github.com/ZIMO-Elektronik/CMakeModules
  GIT_PROGRESS TRUE
  SOURCE_DIR ${CMAKE_BINARY_DIR}/CMakeModules)
FetchContent_MakeAvailable(CMakeModules)

project(
  ZTL
  VERSION 0.16.1
  LANGUAGES CXX)

add_library(ZTL INTERFACE)
add_library(ZTL::ZTL ALIAS ZTL)

target_compile_features(ZTL INTERFACE cxx_std_23)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  target_include_directories(ZTL INTERFACE include)
else()
  target_include_directories(ZTL SYSTEM INTERFACE include)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
