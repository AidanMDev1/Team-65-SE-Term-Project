cmake_minimum_required(VERSION 3.14)
project(ProjectBase)

set(CMAKE_CXX_STANDARD 17)

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
        src/ProjectWindow.h
        src/AchNotWindow.h
        src/Achievements.h)

add_executable(ProjectBase ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR C:SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(ProjectBase sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# catch2 environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # seems to work with CLion - if you run into problems, try an older version of catch2 v3
)
FetchContent_MakeAvailable(Catch2)

include_directories(test-unit)
add_executable(Tests
        test-unit/test.cpp)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) #link catch to test.cpp file
# the name here must match that of your testing executable (the one that has test.cpp)