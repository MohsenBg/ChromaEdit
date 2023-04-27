cmake_minimum_required(VERSION 3.10)

project(ChromaEdit)

execute_process(
    COMMAND pkg-config --libs vips
    OUTPUT_VARIABLE VIPS_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Packages
find_package(GTest REQUIRED)

#find_package(VIPS REQUIRED)

# Find source files
file(GLOB SRCS "foundation/src/*.cpp")
file(GLOB_RECURSE HDRS "foundation/src/*.hpp")

# ChromaEditLib library target
add_library(ChromaEditLib ${SRCS} ${HDRS})
target_link_libraries(ChromaEditLib PRIVATE ${VIPS_LIBS})
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
