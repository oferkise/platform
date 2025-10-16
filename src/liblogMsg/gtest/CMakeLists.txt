cmake_minimum_required(VERSION 3.10)

# Find GTest
find_package(GTest REQUIRED)

# Add test source file
add_executable(gtestLogger gtestLogger.cpp)

# Link with GTest and pthread
target_link_libraries(gtestLogger PRIVATE GTest::gtest GTest::gtest_main pthread logMsg)

# Optionally, set C++ standard
set_target_properties(gtestLogger PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

# Add test to CTest
add_test(NAME gtestLogger COMMAND gtestLogger)
# Enable CTest
enable_testing()
