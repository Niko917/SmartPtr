cmake_minimum_required(VERSION 3.10)
project(SmartPtrs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.0
)

FetchContent_MakeAvailable(googletest)

add_executable(SmartPtrs
    src/main.cpp
)

target_include_directories(SmartPtrs PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(test_smart_pointers
    tests/UniqueTests.cpp
)


target_include_directories(test_smart_pointers PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(test_smart_pointers
    GTest::gtest
    GTest::gtest_main
)

enable_testing()
add_test(NAME test_smart_pointers COMMAND test_smart_pointers)
