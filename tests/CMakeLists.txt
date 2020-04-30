set(TEST_NAME lmdbxxstests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third-party)

file(GLOB SRCS *.cpp)

add_executable(${TEST_NAME} ${SRCS})

target_include_directories(${TEST_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../
)

if(NOT MSVC AND NOT APPLE)
    # some way to resolve cyclic dependencies
  set(LINKER_START_GROUP "-Wl,--start-group")
  set(LINKER_END_GROUP "-Wl,--end-group")
endif()

target_link_libraries(${TEST_NAME} ${LINKER_START_GROUP} gtest gmock signals ${LINKER_END_GROUP})

add_test(NAME ${TEST_NAME}
        COMMAND ${TEST_NAME})

configure_msvc_runtime()