cmake_minimum_required(VERSION 2.8.9)
project (TestLibrary)

include_directories(./driver/include)

aux_source_directory(./driver/src DIR_SRCS)

add_executable(main test/main.c ${DIR_SRCS})
