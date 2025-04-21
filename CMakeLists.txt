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
)
