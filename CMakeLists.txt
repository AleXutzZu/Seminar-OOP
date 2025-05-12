cmake_minimum_required(VERSION 3.28)
project("Seminar OOP")

set(CMAKE_CXX_STANDARD 20)

add_executable(program main.cpp domain/MediaItem.cpp repo/MediaItemRepo.cpp
        service/MediaItemService.cpp
        service/MediaItemService.h)