cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake

set(my_value 123)
set(my_project_name "message project")
message("value: ${my_value}, project name: ${my_project_name}")

message("Cmake File Worked...")
message(STATUS "Cmake File Status Worked...")
message(DEBUG "Cmake File Debug Worked...")
message(WARNING "Cmake File WARNING Worked...")
message(FATAL ERROR "Cmake File FATAL ERROR Worked...")

