cmake_minimum_required(VERSION 3.16)
project(claude-code-unlimited CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ccu
    src/main.cpp
    src/watcher.cpp
    src/rotator.cpp
    src/store.cpp
)

target_include_directories(ccu PRIVATE include)

if(WIN32)
    target_link_libraries(ccu PRIVATE userenv)
endif()
