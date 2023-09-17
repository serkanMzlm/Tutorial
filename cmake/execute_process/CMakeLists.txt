cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake
project(myProject)

execute_process(COMMAND ls
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_VARIABLE APP_VERSION_STR
                OUTPUT_STRIP_TRAILING_WHITESPACE)

message("CMAKE_CURRENT_SOURCE_DIR: ${APP_VERSION_STR}")