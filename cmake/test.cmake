include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

set(TEST_NAME test-amx)
add_executable(test-amx ${CMAKE_CURRENT_SOURCE_DIR}/test/test_amx.cpp)
target_link_libraries(${TEST_NAME} ${PROJECT_NAME} gtest_main)
target_include_directories(${TEST_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
gtest_discover_tests(${TEST_NAME})
