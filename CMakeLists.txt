cmake_minimum_required(VERSION 3.8)
project(cpp_mighty_text_adventure_wizzzards)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Area.hpp
        Game.cpp
        Game.h
        Player.h
        Player.cpp
        main.cpp Room.cpp Room.h Item.cpp Item.h)

add_executable(cpp_mighty_text_adventure_wizzzards ${SOURCE_FILES})