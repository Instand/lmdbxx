cmake_minimum_required(VERSION 3.12)

project(lmdb LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_TOPLEVEL_PROJECT TRUE)
else()
    set(IS_TOPLEVEL_PROJECT FALSE)
endif()

macro(configure_msvc_flags)
    if (MSVC)
        if ("${CMAKE_CXX_FLAGS}" MATCHES "([/-]W[0-3])")
            message("Other Flags /W detected, replace it to avoid compiler warning to /W4")
            string(REGEX REPLACE "([/-]W[0-3])" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
        endif()
    endif()
endmacro()

configure_msvc_flags()

add_subdirectory(lmdb)

if(IS_TOPLEVEL_PROJECT)
    enable_testing()
    add_subdirectory(tests)
endif()


add_library(${PROJECT_NAME}    "./lmdbexception.hpp"
                               "./lmdb.hpp"
                               "./lmdb.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "../third-party/lmdb/libraries/liblmdb/")
target_include_directories(${PROJECT_NAME} PUBLIC "../third-party/lmdbxx/")
target_include_directories(${PROJECT_NAME} PUBLIC "./"
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../lib/include)

target_link_libraries(${PROJECT_NAME} lmdb signals)