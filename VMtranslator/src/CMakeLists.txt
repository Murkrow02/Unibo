cmake_minimum_required(VERSION 3.20)
project(src C)

set(CMAKE_C_STANDARD 99)

add_executable(src main.c TranslationTable.c Headers/TranslationTable.h Utils.c Headers/Utils.h)
