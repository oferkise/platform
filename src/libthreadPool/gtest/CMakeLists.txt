cmake_minimum_required(VERSION 3.10)

# Find GTest
find_package(GTest REQUIRED)

# Add test source file
add_executable(gtestThreadPool gtestThreadPool.cpp)

# Link with GTest and pthread
target_link_libraries(gtestThreadPool PRIVATE GTest::gtest GTest::gtest_main pthread threadPool)

# Optionally, set C++ standard
set_target_properties(gtestThreadPool PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

# Add test to CTest
add_test(NAME gtestThreadPool COMMAND gtestThreadPool)
# Enable CTest
enable_testing()
