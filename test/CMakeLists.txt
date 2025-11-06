set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

# ===============================
# Test executable
# ===============================
add_executable(run_tests ${TEST_SOURCES})

target_include_directories(run_tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/game
        ${CMAKE_SOURCE_DIR}/engine/include
)

# Link against engine and Catch2
target_link_libraries(run_tests
    PRIVATE
        engine
        Catch2::Catch2WithMain
)

# ===============================
# Register tests
# ===============================
include(Catch)
catch_discover_tests(run_tests)
