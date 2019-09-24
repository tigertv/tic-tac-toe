cmake_minimum_required (VERSION 2.6)

project (tic-tac-toe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(tic-tac-toe tic-tac-toe.cpp Board.cpp Game.cpp HumanPlayer.cpp AiPlayer.cpp BoardCell.cpp)
