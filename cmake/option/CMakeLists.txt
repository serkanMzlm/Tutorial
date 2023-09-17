cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake

project(myProject)

option(ENABLE_FEATURE "Enable feature X" OFF)

if(ENABLE_FEATURE)
  message(STATUS "Feature X is enabled")
else()
  message(STATUS "Feature X is disabled")
endif()

