cmake_minimum_required(VERSION 3.10)

add_library(threadPool SHARED
    FixedThreadPool.cpp
)

target_include_directories(threadPool
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS threadPool
    EXPORT threadPoolTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES
    ThreadPool.h
    DESTINATION include
)

add_subdirectory(gtest)
