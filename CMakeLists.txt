cmake_minimum_required(VERSION 3.8)
project(stereo_reader)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCES
        src/Prompter.h src/Prompter.cpp
        src/ImageData.h
        src/processing.h src/processing.cpp
        src/writing.h src/writing.cpp
        src/Correlation.h src/PairList.cpp src/PairList.h)

add_executable(stereo_reader src/main.cpp ${SOURCES})
target_link_libraries(stereo_reader ${OpenCV_LIBS} ${Boost_LIBRARIES})

add_executable(thresh_test src/thresh_test.cpp)
target_link_libraries(thresh_test ${OpenCV_LIBS})

add_executable(testing test/main.cpp ${SOURCES})
target_link_libraries(testing ${OpenCV_LIBS}
        ${Boost_LIBRARIES} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

add_test(mytest testing)
