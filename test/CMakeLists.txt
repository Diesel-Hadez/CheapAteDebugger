cmake_minimum_required(VERSION 3.14)
include(FetchContent)
cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hello_test
  hello_test.cc
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

add_executable(
  chip8_emulation
  chip8_emulation.cc
)

target_link_libraries(
  chip8_emulation
  GTest::gtest_main
  CheapAteDebugger_lib
)

include(GoogleTest)
gtest_discover_tests(hello_test)

