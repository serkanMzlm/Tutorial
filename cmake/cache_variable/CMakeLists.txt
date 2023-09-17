cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake
project(myProject)
set(VAR "12" CACHE STRING "This command sets variable A in persistent cache") #last parameter short description
message($CACHE{VAR})
set(VAR "19" CACHE STRING "change the value" FORCE)
message($ENV{PATH})
