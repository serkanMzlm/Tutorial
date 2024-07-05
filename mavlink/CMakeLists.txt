cmake_minimum_required(VERSION 3.0.0)
project(mavlink_comm)

list(APPEND CMAKE_PREFIX_PATH "/home/serkan/source_code/mavlink/install")

find_package(MAVLink REQUIRED)

file(GLOB SRC_FILE ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/inc)

add_library(mavlink_lib ${SRC_FILE})

add_executable(${PROJECT_NAME} test/main.cpp)
add_executable(sender test/sender.cpp)
add_executable(receiver test/receiver.cpp)

target_link_libraries(mavlink_lib PUBLIC MAVLink::mavlink)
target_link_libraries(sender PRIVATE MAVLink::mavlink)
target_link_libraries(receiver PRIVATE MAVLink::mavlink)
target_link_libraries(${PROJECT_NAME} PUBLIC mavlink_lib)