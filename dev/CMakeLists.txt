cmake_minimum_required(VERSION 3.20)
project(TCMS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable clang-tidy
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=modernize-*,performance-*")

# Use Ninja
set(CMAKE_GENERATOR "Ninja")

# Add vcpkg (manifest mode)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/lib/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Include directories (Headers)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subdirectories
add_subdirectory(src)  # Includes src/CMakeLists.txt
add_subdirectory(tests)  # Includes tests/CMakeLists.txt

# Enable testing
enable_testing()

# Find packages
# find_package(GTest CONFIG REQUIRED)

# # Define the executable
# add_executable(tcms src/main.cpp)

# # Link Google Test
# target_link_libraries(tcms PRIVATE GTest::gtest_main)

# enable_testing()
# add_test(NAME tcms_test COMMAND tcms)
