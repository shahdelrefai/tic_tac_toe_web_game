cmake_minimum_required(VERSION 3.24)
project(TicTacToeGame-Server C)

set(CMAKE_C_STANDARD 11)

add_executable(TicTacToeGame-Server main.c TicTacToeGame.h TicTacToeGame.c mysocket.h mysocket.c)
