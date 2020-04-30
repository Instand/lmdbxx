cmake_minimum_required(VERSION 3.12)

project(lmdbxx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_TOPLEVEL_PROJECT TRUE)
else()
    set(IS_TOPLEVEL_PROJECT FALSE)
endif()

if (MSVC)
    add_definitions(-DNOMINMAX)
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_definitions(-D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING)
    add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
    add_definitions(-D_ENABLE_EXTENDED_ALIGNED_STORAGE)
endif()

macro(configure_msvc_runtime)
    if (MSVC)
        if ("${MSVC_RUNTIME}" STREQUAL "")
            set(MSVC_RUNTIME "static")
        endif()

        set(variables
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_MINSIZEREL
            CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS_RELMONITOR
            CMAKE_C_FLAGS_RELWALLET
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_MINSIZEREL
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_RELMONITOR
            CMAKE_CXX_FLAGS_RELWALLET
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
            )
        if (${MSVC_RUNTIME} STREQUAL "static")
            message(STATUS
                "MSVC -> forcing use of statically-linked runtime."
                )
            foreach(variable ${variables})
                if (${variable} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
                endif()
            endforeach()
        else()
            message(STATUS
                "MSVC -> forcing use of dynamically-linked runtime."
                )
            foreach(variable ${variables})
                if (${variable} MATCHES "/MT")
                    string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
                endif()
            endforeach()
        endif()
    endif()
endmacro()

macro(match_and_replace type from to)
    if ("${${type}}" MATCHES ${from})
        string(REGEX REPLACE ${from} ${to} ${type} ${${type}})
    endif()
endmacro()

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

macro(configure_third_party_compiler_flags)
    if (MSVC)
        if ("${CMAKE_CXX_FLAGS}" MATCHES "([/-]W[1-4])")
            message("Other Flags /W detected, replace it to suppress third party warnings")
            match_and_replace(CMAKE_CXX_FLAGS "([/-]W[0-4])" "/W0")
            match_and_replace(CMAKE_C_FLAGS "([/-]W[0-4])" "/W0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
        endif()
    endif()
endmacro()

configure_msvc_flags()
configure_msvc_runtime()

add_subdirectory(lmdb)

if (IS_TOPLEVEL_PROJECT)
    enable_testing()
    add_subdirectory(tests)
endif()


add_library(${PROJECT_NAME}    "./lmdbexception.hpp"
                               "./lmdb.hpp"
                               "./lmdb.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "./third-party/lmdb/libraries/liblmdb/")
target_include_directories(${PROJECT_NAME} PUBLIC "./third-party/lmdbxx/")

target_link_libraries(${PROJECT_NAME} lmdb signals)
