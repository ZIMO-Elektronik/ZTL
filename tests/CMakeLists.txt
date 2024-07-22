include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ZTLTests ${SRC})

sanitize(address,undefined)

target_common_warnings(ZTLTests PRIVATE)

target_compile_options(ZTL INTERFACE -Werror;-Wno-error=deprecated-declarations)

cpmaddpackage(
  NAME
  googletest
  GITHUB_REPOSITORY
  "google/googletest"
  GIT_TAG
  main
  SYSTEM
  YES
  OPTIONS
  "INSTALL_GTEST OFF")

target_link_libraries(ZTLTests PRIVATE ZTL::ZTL GTest::gtest_main GTest::gmock)

gtest_discover_tests(ZTLTests)
