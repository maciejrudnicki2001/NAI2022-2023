cmake_minimum_required(VERSION 3.21)
project(myFirstCVproject1)

set(CMAKE_CXX_STANDARD 23)
set(ENV ${OpenCV_DIR} )
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(myFirstCVproject1 main.cpp)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(myFirstCVproject1 ${OpenCV_LIBS})
