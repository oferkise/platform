cmake_minimum_required(VERSION 3.10)

add_library(logMsg SHARED
    Logger.cpp
    LoggerCfg.cpp
)

target_include_directories(logMsg
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(logMsg util)

install(TARGETS logMsg
    EXPORT logMsgTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES
    Logger.h
    LoggerCfg.h
    DESTINATION include
)

add_subdirectory(gtest)
