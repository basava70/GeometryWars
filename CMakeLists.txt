cmake_minimum_required(VERSION 4.0.3)

set(PROJECT_NAME GeometryWars)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image  REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

option(BUILD_GAME "Build the GeometryWars game executable" ON)
option(BUILD_TEST "Build unit tests" ON)

if(BUILD_GAME)
  message(STATUS "Found SDL3 version: ${SDL3_VERSION}")
  message(STATUS "Found SDL3_image version: ${SDL3_image_VERSION}")
  message(STATUS "Found SDL3_ttf_version: ${SDL3_ttf_VERSION}")

  file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS engine/src/*.cpp)
  set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
  set(GAME_SOURCE ${CMAKE_SOURCE_DIR}/game/Game.cpp)

  add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${ENGINE_SOURCES}
  ${GAME_SOURCE})

  set(ENGINE_INCLUDE ${CMAKE_SOURCE_DIR}/engine/include)
  set(GAME_INCLUDE ${CMAKE_SOURCE_DIR}/game)
  target_include_directories(${PROJECT_NAME} PRIVATE ${ENGINE_INCLUDE}
  ${GAME_INCLUDE})

  target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3
  SDL3_image::SDL3_image
SDL3_ttf::SDL3_ttf)
endif()

if(BUILD_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
