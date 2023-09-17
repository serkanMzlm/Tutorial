cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake
project(myProject)
set(my_log_FOUND 1)

message(${CMAKE_INSTALL_PREFIX})

add_library(myLog  STATIC src/myLog/log_data.cpp)
add_executable(main main.cpp)

target_link_libraries(main PUBLIC myLog)

# this command can cause "INTERFACE_INCLUDE_DIRECTORIES property contains path:" error
# target_include_directories(myLog PUBLIC ${CMAKE_HOME_DIRECTORY}/include/myLog) 
target_include_directories(myLog PUBLIC 
        $<INSTALL_INTERFACE:include/myLog>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/myLog>
)

        install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/myLog/log_data.hpp 
                DESTINATION ${CMAKE_INSTALL_PREFIX}/include/myLog)

install(TARGETS myLog EXPORT my_export DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/myLog)

#With find_package, this file is copied to the appropriate form and to the appropriate location so that this file can be found. FILE in this section is used to name the file to be copied.
install(EXPORT my_export FILE my_logConfig.cmake  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/myLog)

