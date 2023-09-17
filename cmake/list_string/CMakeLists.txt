cmake_minimum_required(VERSION 3.10)  #Sets the minimum cmake version to run cmake

set(var 123 3;4;"aa" "bb" cc)
list(APPEND var 2.0 "dd")     #Adds to the end of the list
list(REMOVE_AT var 0 3)       #Deletes values ​​found in index 0 and 3
list(REMOVE_ITEM var aa bb)   #Deletes aa and bb from the list
list(INSERT var 2 XX YY 3.7)  #Writes the specified parameters starting from the 2nd index
list(REVERSE var)             #Reverses
list(REMOVE_DUPLICATES var)   #Deletes the same data
list(SORT var)                #sorts the list

message("${var}")

set(name_var "Name Var")
string(TOLOWER ${name_var} lower_case)
string(TOUPPER ${name_var} upper_case)
message(${lower_case})
message(${upper_case})



