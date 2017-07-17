cmake_minimum_required(VERSION 3.8)
project(stereo_reader)

set(CMAKE_CXX_STANDARD 11)



find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

add_executable(stereo_reader src/main.cpp)
target_link_libraries(stereo_reader ${OpenCV_LIBS})

add_executable(thresh_test src/thresh_test.cpp)
target_link_libraries(thresh_test ${OpenCV_LIBS})
