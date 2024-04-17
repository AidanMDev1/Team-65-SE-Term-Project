cmake_minimum_required(VERSION 3.0)
project(Database)

find_package(CURL REQUIRED)

add_executable(run backendtest.cpp request.h request.cpp)

target_link_libraries(run CURL::libcurl)
