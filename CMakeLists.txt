cmake_minimum_required(VERSION 3.2)
project(ASKSYSTEM)
set(SRC_FILES
    src/ask_main.cpp
    src/system/system.cpp
    components/src/ask.cpp
    components/src/question.cpp
    components/src/thread.cpp
    components/src/user.cpp)

add_executable(asksystem ${SRC_FILES})
target_include_directories(asksystem PUBLIC 
                            components/include/
                            src/system/)