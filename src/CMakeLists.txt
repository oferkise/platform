cmake_minimum_required(VERSION 3.10)
project(oferkise_platform_CXX)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

add_subdirectory(libutil)
add_subdirectory(liblogMsg)
add_subdirectory(libthreadPool)
