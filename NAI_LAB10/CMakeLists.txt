cmake_minimum_required(VERSION 3.24)
project(myArucoFIrstProject)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 17)
add_executable(myArucoFIrstProject main.cpp)
target_link_libraries(myArucoFIrstProject ${OpenCV_LIBS})
