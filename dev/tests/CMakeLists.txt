# Find packages
find_package(GTest CONFIG REQUIRED)

# Link Google Test
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
add_executable(tcms_tests ${TEST_SOURCES})
target_link_libraries(tcms_tests PRIVATE GTest::gtest_main)

add_test(NAME tcms_tests COMMAND tcms_tests)