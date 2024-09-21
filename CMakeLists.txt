cmake_minimum_required(VERSION 3.30)

project(SmartPointers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") #-fsanitize=address")

include_directories(${CMAKE_SOURCE_DIR}/include)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_MakeAvailable(ftxui)
endif()
# ------------------------------------------------------------------------------

set(CMAKE_TOOLCHAIN_FILE /opt/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(GTest REQUIRED)

if(GTEST_FOUND)
    add_executable(SmartPointers src/main.cpp)

    enable_testing()

    target_link_libraries(SmartPointers ftxui::dom ftxui::screen ftxui::component)

    add_executable(unique_tests tests/UniqueTests.cpp)
    add_executable(weak_tests tests/WeakTests.cpp)
    add_executable(shared_tests tests/SharedTests.cpp)
    
    target_link_libraries(unique_tests GTest::GTest)
    target_link_libraries(shared_tests GTest::GTest)
    target_link_libraries(weak_tests GTest::GTest)

    add_test(NAME unique_tests COMMAND unique_tests)
    add_test(NAME shared_tests COMMAND shared_tests)
    add_test(NAME weak_tests COMMAND weak_tests)
endif()
