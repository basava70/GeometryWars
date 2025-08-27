cmake_minimum_required(VERSION 4.0.3)
project(EngineTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)

add_executable(run_tests TestComponentArray.cpp)

target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/engine/include)

target_link_libraries(run_tests PRIVATE Catch2::Catch2WithMain)
enable_testing()

add_test(NAME ecs_component_array COMMAND run_tests)
