cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake
project(myProject LANGUAGES C CXX ASM VERSION 1.0) #Set the version, project name and languages ​​used in the project for the project.

add_library(my_add  add.cpp)   #libraries are specified
add_library(my_print print.cpp)

add_executable(my_project main.cpp) #sets the files that need to be compiled for the executable and sets the name of the resulting file

target_link_libraries(my_project my_add my_print) #library and main file linked. PRIVATE and PUBLIC keywords can be used
