cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY "https://github.com/ZIMO-Elektronik/CMakeModules"
  GIT_TAG v0.9.3
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

if(PROJECT_IS_TOP_LEVEL)
  target_include_directories(ZTL INTERFACE include)
else()
  target_include_directories(ZTL SYSTEM INTERFACE include)
endif()

target_common_warnings(ZTL INTERFACE)

if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
  file(
    DOWNLOAD
    "https://github.com/ZIMO-Elektronik/.clang-format/raw/master/.clang-format"
    ${CMAKE_CURRENT_LIST_DIR}/.clang-format)
  file(GLOB_RECURSE SRC include/*.*pp tests/*.*pp)
  add_clang_format_target(ZTLFormat OPTIONS -i FILES ${SRC})
endif()

if(BUILD_TESTING
   AND PROJECT_IS_TOP_LEVEL
   AND CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
  add_subdirectory(tests)
endif()
