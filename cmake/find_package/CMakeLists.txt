cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake
project(my_project)

# list(APPEND CMAKE_MODULE_PATH "/usr/local/lib/myLog/")
set(my_log_DIR "/usr/local/lib/myLog/")

find_package(my_log CONFIG REQUIRED)

if(my_log_FOUND)
    message("my_log library found")
    add_executable(main main.cpp)
    target_link_libraries(main  myLog)

else()
    message(FATTAL_ERROR "my_log library not found")
    message("pat:${CMAKE_PREFIX_PATH}")
endif()

