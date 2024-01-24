cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        rbt/rbt.c
        data_structure.h
        rbt/rbt.h
        rbt/rbt_util.c
        rbt/test.c)
