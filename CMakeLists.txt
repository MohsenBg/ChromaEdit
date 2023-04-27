cmake_minimum_required(VERSION 3.10)

project(ChromaEdit)

# Packages
find_package(GTest REQUIRED)

# Find source files
file(GLOB SRCS "foundation/src/*.cpp")
file(GLOB_RECURSE HDRS "foundation/src/*.hpp")

# ChromaEditLib library target
add_library(ChromaEditLib ${SRCS} ${HDRS})
target_include_directories(ChromaEditLib PUBLIC ${CMAKE_SOURCE_DIR}/foundation)

# Main executable target
add_executable(ChromaEdit ${CMAKE_SOURCE_DIR}/foundation/main.cpp)
target_link_libraries(ChromaEdit PUBLIC ChromaEditLib)

# Test executable target
add_executable(TestChromaEdit ${CMAKE_SOURCE_DIR}/foundation/test/reader.test.cpp ${SRCS})
target_include_directories(TestChromaEdit PUBLIC ${CMAKE_SOURCE_DIR}/foundation)
target_link_libraries(TestChromaEdit PUBLIC ChromaEditLib GTest::GTest GTest::Main)

# Register test
add_test(NAME reader.test COMMAND TestChromaEdit)
