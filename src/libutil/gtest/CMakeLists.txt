cmake_minimum_required(VERSION 3.10)

# Find GTest
find_package(GTest REQUIRED)

# Enable CTest
enable_testing()

# Add test source file
add_executable(gtestUtil gtestDateTime.cpp gtestCfgFile.cpp)

# Link with GTest and pthread
target_link_libraries(gtestUtil PRIVATE GTest::gtest GTest::gtest_main pthread logMsg)

# Optionally, set C++ standard
set_target_properties(gtestUtil PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

# Add test to CTest
add_test(NAME gtestUtil COMMAND gtestUtil)
