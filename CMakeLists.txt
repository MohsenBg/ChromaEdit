cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

project(ChromaEdit)

# Packages
find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)


# Find source files
file(GLOB SRCS "foundation/src/*.cpp")
file(GLOB_RECURSE HDRS "foundation/src/*.hpp")

# ChromaEditLib library target
add_library(ChromaEditLib ${SRCS} ${HDRS})
target_include_directories(ChromaEditLib PUBLIC ${CMAKE_SOURCE_DIR}/foundation)
target_include_directories(ChromaEditLib PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(ChromaEditLib ${OpenCV_LIBS})

# Main executable target
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/foundation/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC ChromaEditLib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})


set(TESTCPP
    ${CMAKE_SOURCE_DIR}/foundation/test/reader.test.cpp
    ${CMAKE_SOURCE_DIR}/foundation/test/image_editor.test.cpp
    # add more source files as needed
)

# Test executable target
add_executable(TestChromaEdit ${TESTCPP})
target_include_directories(TestChromaEdit PUBLIC ${CMAKE_SOURCE_DIR}/foundation)
target_link_libraries(TestChromaEdit PUBLIC ChromaEditLib GTest::GTest GTest::Main)


# Register test
add_test(NAME reader.test COMMAND TestChromaEdit)
