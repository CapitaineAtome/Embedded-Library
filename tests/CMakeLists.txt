cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME "Tests-Library")

project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(../library)

enable_testing()

# Build the library
add_executable(Tests_Library
        commons/tests_commons.cpp
        commons/test_lambada.cpp)

target_link_libraries(
        Tests_Library
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests_Library)