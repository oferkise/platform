cmake_minimum_required(VERSION 3.10)

# Find GTest
find_package(GTest REQUIRED)

# Add test source file
add_executable(gtestDateTime gtestDateTime.cpp)

# Link with GTest and pthread
target_link_libraries(gtestDateTime PRIVATE GTest::gtest GTest::gtest_main pthread logMsg)

# Optionally, set C++ standard
set_target_properties(gtestDateTime PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

# Add test to CTest
add_test(NAME gtestDateTime COMMAND gtestDateTime)
# Enable CTest
enable_testing()
