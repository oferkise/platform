cmake_minimum_required(VERSION 3.10)

add_library(util SHARED
    DateTime.cpp
    CfgFile.cpp
)

target_include_directories(util
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS util
    EXPORT utilTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES
    DateTime.h
    DESTINATION include
)

add_subdirectory(gtest)
