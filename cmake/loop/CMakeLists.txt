cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake

set(VAR a)
while(NOT VAR STREQUAL "aaaaaaaaa")
    set(VAR ${VAR}a)
    message(${VAR})
endwhile()


foreach(Name "serkan" "ali" mert 10)
    message(${Name})
endforeach()

foreach(number RANGE 10 1000 300)
    message(${number})
endforeach()

set(x 1 2 3 4 5 6 7 "8 9" 10;11)
foreach(number IN LISTS x)
    message("x: ${number}")
endforeach()

