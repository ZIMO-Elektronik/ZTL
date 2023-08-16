cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY https://github.com/ZIMO-Elektronik/CMakeModules
  GIT_TAG v0.2.0
  SOURCE_DIR ${CMAKE_BINARY_DIR}/CMakeModules)
FetchContent_MakeAvailable(CMakeModules)

version_from_git()
project(
  ZTL
  VERSION ${VERSION_FROM_GIT}
  LANGUAGES CXX)

add_library(ZTL INTERFACE)
add_library(ZTL::ZTL ALIAS ZTL)

target_compile_features(ZTL INTERFACE cxx_std_23)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  target_include_directories(ZTL INTERFACE include)
  target_compile_options(ZTL
                         INTERFACE -Werror;-Wno-error=deprecated-declarations)
  sanitize("address,undefined")
else()
  target_include_directories(ZTL SYSTEM INTERFACE include)
endif()

target_common_warnings(ZTL INTERFACE)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

if(BUILD_TESTING
   AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME
   AND CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
  add_subdirectory(tests)
endif()
