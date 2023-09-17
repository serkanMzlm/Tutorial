cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake
project(myProject LANGUAGES CXX VERSION 1.0) #Set the version, project name and languages ​​used in the project for the project.

if(UNIX)
    add_definitions(-DCMAKEMACROSAMPLE="Linux")
    add_definitions(-std=c++11)
endif()

add_executable(my_project 
                main.cpp) #sets the files that need to be compiled for the executable and sets the name of the resulting file

