cmake_minimum_required(VERSION 3.0)

project(idz)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(PUBLIC_HEADERS MeanShift.h)

set(HEADERS ${PUBLIC_HEADERS})

set(SOURCES MeanShift.cpp Maincpp.cpp)

add_executable(idz ${HEADERS} ${SOURCES})

target_link_libraries(idz ${OpenCV_LIBS})
