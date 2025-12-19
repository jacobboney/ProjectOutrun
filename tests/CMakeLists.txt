include(FetchContent)

set(gtest_disable_pthreads ON)
set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

# Prevent GoogleTest from overriding your compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

find_package(Threads REQUIRED)

set(TEST_SOUTRCE_FILES
    instructions_test.cpp
)

add_executable(core6502_tests
    ${TEST_SOUTRCE_FILES}
)

target_link_libraries(core6502_tests
    PRIVATE
        core6502
        GTest::gtest
        GTest::gtest_main
        Threads::Threads
)

# MinGW sometimes still needs this explicitly
if (MINGW)
    target_link_libraries(core6502_tests PRIVATE winpthread)
endif()

include(GoogleTest)
gtest_discover_tests(core6502_tests)