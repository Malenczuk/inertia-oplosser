cmake_minimum_required(VERSION 3.14)
project(DiamondsAndMines)

set(CMAKE_CXX_STANDARD 11)

add_executable(DiamondsAndMines src/main.cpp src/board/Board.cpp src/board/Board.h src/board/Field.cpp src/board/Field.h src/board/Move.cpp src/board/Move.h)