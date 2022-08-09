cmake_minimum_required(VERSION 3.22)
project(banking_record_system)
set(CMAKE_CXX_STANDARD 14)

include_directories(.)

set(SOURCE_FILES
        BankAccount.cpp
        BankAccount.h
        main.cpp)

add_executable(banking_record_system ${SOURCE_FILES})
