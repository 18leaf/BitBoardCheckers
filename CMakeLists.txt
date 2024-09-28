cmake_minimum_required(VERSION 3.29)
project(BitBoardCheckers)

set(CMAKE_CXX_STANDARD 20)

# Include all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Include directories
include_directories(src)

add_executable(BitBoardCheckers src/main.cpp
        src/utils/BitManipulationUtility.cpp
        src/utils/BitManipulationUtility.h
        src/game/CheckersGame.cpp
        src/game/CheckersGame.h
        src/game/Board.cpp
        src/game/Board.h
        src/game/Move.cpp
        src/game/Move.h
        src/game/Player.cpp
        src/game/Player.h
        src/exceptions/InvalidMoveException.cpp
        src/exceptions/InvalidMoveException.h)
