include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ZTLTests ${SRC})

sanitize("address,undefined")

target_common_warnings(ZTLTests PRIVATE)

cpmaddpackage("gh:google/googletest#main")

target_link_libraries(ZTLTests PRIVATE ZTL::ZTL GTest::gtest GTest::gmock)

gtest_discover_tests(ZTLTests)
