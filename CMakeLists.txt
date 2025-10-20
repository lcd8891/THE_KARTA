cmake_minimum_required(VERSION 3.30)
project("THE MAP")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS graphics window system audio REQUIRED)

add_executable(MANI WIN32 mani.cpp)
target_link_libraries(MANI PRIVATE sfml-graphics sfml-system sfml-audio sfml-window)
set_target_properties(MANI PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/out)