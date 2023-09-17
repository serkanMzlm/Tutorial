add_library(my_libs add.cpp print.cpp)
target_include_directories(my_libs PUBLIC ${PROJECT_SOURCE_DIR}/inc) #we indicate where the header is