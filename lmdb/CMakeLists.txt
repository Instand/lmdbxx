cmake_minimum_required(VERSION 3.10)

project(lmdb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_third_party_compiler_flags()

add_library(${PROJECT_NAME} STATIC "${CMAKE_SOURCE_DIR}/third-party/lmdb/libraries/liblmdb/lmdb.h"
                                   "${CMAKE_SOURCE_DIR}/third-party/lmdb/libraries/liblmdb/mdb.c"
                                   "${CMAKE_SOURCE_DIR}/third-party/lmdb/libraries/liblmdb/mdb_copy.c"
                                   "${CMAKE_SOURCE_DIR}/third-party/lmdb/libraries/liblmdb/midl.h"
                                   "${CMAKE_SOURCE_DIR}/third-party/lmdb/libraries/liblmdb/midl.c")

target_include_directories(${PROJECT_NAME} PRIVATE "../third-party/lmdb/libraries/liblmdb/")
