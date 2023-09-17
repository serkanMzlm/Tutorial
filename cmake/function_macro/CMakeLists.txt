cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake

function(print_name)
    message("my name is mert")
endfunction()

function(add param)
    message("param: ${param}")
endfunction()

set(VAR "yunus")
print_name()
print_name()
add(100)
add("Yakup")
add(${VAR})


function(my_func name)
    message("ARGC: ${ARGC}")
    message("ARGV: ${ARGV}")
    message("ARGN: ${ARGN}")
    foreach(name ${ARGV})
        message("my name is ${name}")
    endforeach()
endfunction()

my_func(ali mert serkan)


set(myVar 12)
function(setVar)
    message("var: ${myVar}")
    set(myVar 10)
    message("var: ${myVar}")
endfunction()
 
message("var: ${myVar}")
setVar()
message("var: ${myVar}")

message("-------")
set(myVar2 13)
function(setVar2)
    message("var: ${myVar2}")
    set(myVar2 10 PARENT_SCOPE)
    message("var: ${myVar2}")
endfunction()
 
message("var: ${myVar2}")
setVar2()
message("var: ${myVar3}")

message("-------")
set(myVar2 13)
macro(setVar3)
    message("var: ${myVar2}")
    set(myVar3 10 )
    message("var: ${myVar2}")
endmacro()
 
message("var: ${myVar2}")
setVar3()
message("var: ${myVar3}")

