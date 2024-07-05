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
add_executable(client client.cpp)
add_executable(server server.cpp)
add_executable(client_serial client_serial.cpp)
add_executable(server_serial server_serial.cpp)

target_link_libraries(mavlink_lib PUBLIC MAVLink::mavlink)
target_link_libraries(sender PRIVATE MAVLink::mavlink)
target_link_libraries(receiver PRIVATE MAVLink::mavlink)
target_link_libraries(server PRIVATE MAVLink::mavlink)
target_link_libraries(client PRIVATE MAVLink::mavlink)
target_link_libraries(server_serial PRIVATE MAVLink::mavlink)
target_link_libraries(client_serial PRIVATE MAVLink::mavlink)
target_link_libraries(${PROJECT_NAME} PUBLIC mavlink_lib)