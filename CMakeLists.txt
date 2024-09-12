cmake_minimum_required(3.20)

project(SmartPointers)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g$")


target_include_directories(SmartPointers PUBLIC ${CMAKE_SOURCE_DIR}/include)



find_package(GTest REQUIRED)

if(GTEST_FOUND)

    set(GTEST_INCLUDE_DIR "usr/include")
    set(GTEST_LIBRARY "/usr/lib/libgtest.a")
    set(GTEST_MAIN_LIBRARY "/usr/lib/libgtest_main.a")

    
    add_executable(SmartPointers src/main.cpp)

    enable_testing()
    add_executable(unique_tests tests/UniqueTests.cpp)

    #add_executable(shared_tests tests/SharedTests.cpp)

    target_link_libraries(unique_tests Gtest::gtest Gtest::gtest_main)
    
    target_link_libraries(shared_tests Gtest::gtest Gtest::gtest_main)

    add_test(NAME unique_tests COMMAND unique_tests)
    add_test(NAME shared_tests COMMAND shared_tests)

endif()
