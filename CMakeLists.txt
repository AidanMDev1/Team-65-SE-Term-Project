set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.14)
project(Database)

set(SOURCE_FILES
        src/main.cpp
        src/UserAccount.h
        src/UserAccount.cpp
        src/UserRoles.cpp
        src/Textbox.h
        src/Button.h
        src/Windows.h
        src/LoginWindow.h
        src/MainWindow.h
        src/TimesWindow.h
        src/AchNotWindow.h
        src/request.h
        src/request.cpp)

set(SFML_DIR C:SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
find_package(CURL REQUIRED) 

add_executable(run ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

include_directories(c:/SFML/include)

target_link_libraries(run CURL::libcurl sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

