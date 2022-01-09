cmake_minimum_required(VERSION 3.10)

# set the project name
project(spz_cpp)

# add the executable
file(GLOB project_src "*.hpp" "*.cpp")

add_executable(spz_cpp ${project_src} )

execute_process(COMMAND "./spz_cpp")