cmake_minimum_required(VERSION 3.30)
project(BugBattle)

set(CMAKE_CXX_STANDARD 20)

add_executable(BugBattle main.cpp
        Bug.cpp
        Bug.h
        Crawler.cpp
        Crawler.h
        Board.cpp
        Board.h
        Position.h
        Direction.h
        BugType.h
        Hopper.cpp
        Hopper.h
        wallHugger.cpp
        wallHugger.h
        SuperBug.cpp
        SuperBug.h
        SFMLSimulation.cpp
        SFMLSimulation.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.2/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics network REQUIRED)

include_directories(C:/SFML-2.6.2/include)
target_link_libraries(BugBattle sfml-system sfml-window sfml-graphics)
