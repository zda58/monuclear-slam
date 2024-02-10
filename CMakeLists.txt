cmake_minimum_required(VERSION 3.16)
project(mslam)

set(CMAKE_CXX_STANDARD 20)

add_executable(mslam src/main.cpp)
add_subdirectory(src)

find_package(SDL2 REQUIRED)
find_package(OpenCV REQUIRED)

target_include_directories(mslam PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS})

target_link_libraries(mslam PRIVATE 
    ${SDL2_LIBRARIES}
    ${OpenCV_LIBS})

#target_compile_options(mslam PRIVATE
#    -Isrc/
#    -lSDL2main 
#    -lSDL2)

