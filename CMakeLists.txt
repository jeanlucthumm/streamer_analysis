cmake_minimum_required(VERSION 3.8)
project(stereo_reader)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCES
        src/Prompter.h src/Prompter.cpp
        src/ImageData.h
        src/NameInterpreter.h src/NameInterpreter.cpp
        src/Processor.cpp src/Processor.h src/Correlation.h)

add_executable(stereo_reader src/main.cpp ${SOURCES})
target_link_libraries(stereo_reader ${OpenCV_LIBS} ${Boost_LIBRARIES})

add_executable(thresh_test src/thresh_test.cpp)
target_link_libraries(thresh_test ${OpenCV_LIBS})

add_executable(testing src/testing.cpp ${SOURCES})
target_link_libraries(testing ${OpenCV_LIBS} ${Boost_LIBRARIES})



