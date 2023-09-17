cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake

set(var 0)

if(var) #checks the value inside the variable
    message("true")
else()
    message("false")
endif()

if(DEFINED var)  #checks if the variable exists
    message("Variable found")
else()
    message("Variable not found")
endif()

if(COMMAND project)  
    message("there is command")
else()
    message("No commands")
endif()

if(COMMAND projectt) 
message("there is command")
else()
    message("No commands")
endif()


if(EXISTS ./CMakeLists.txt) 
message("file exists")
else()
    message("no file")
endif()


set(Name1 ali)
set(Name2 mehmet)

if(Name1 STRLESS Name2)
    message("${Name1} is less than ${Name2}")
elseif(Name1 STRGREATER Name2)
    message("${Name1} is greater than ${Name2}")
elseif(Name1 STREQUAL Name2 AND DEFINED var)
    message("${Name1} is equal than ${Name2}")
elseif(Name1 STREQUAL Name2)
    message("${Name1} is equal than ${Name2}")
endif()
