cmake_minimum_required(VERSION 3.16)

project(ProjectOutrun)

set(gtest_disable_pthreads ON)

# Compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

set(HEADER_FILES
    src/bus6502/bus6502.h
    src/cpu6502/cpu6502.h
    src/memory6502/memory6502.h
    src/defines.h)

set(SOURCE_FILES  
    src/bus6502/bus6502.cpp
    src/cpu6502/cpu6502.cpp 
    src/cpu6502/instructions6502.cpp 
    src/memory6502/memory6502.cpp)

add_library(core6502
    ${SOURCE_FILES})

# Install the core6502 library to lib/ and headers to include/
install(TARGETS core6502
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

# Install all public headers to include/core6502
install(FILES
    ${HEADER_FILES}
    DESTINATION include/core6502)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    ${SOURCE_FILES})

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

add_subdirectory(tests)