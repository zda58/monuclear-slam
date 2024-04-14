cmake_minimum_required(VERSION 3.16)
project(mslam)

set(CMAKE_CXX_STANDARD 20)

add_executable(mslam src/main.cpp)
add_subdirectory(src)

find_package(SDL2 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)

target_include_directories(mslam PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}    
    ${GLM_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS})

target_link_libraries(mslam PRIVATE 
    ${SDL2_LIBRARIES}
    ${OpenCV_LIBS}
    ${OPENGL_LIBRARIES}
    ${GLM_LIBRARIES}
    ${GLEW_LIBRARIES})
    
#target_compile_options(mslam PRIVATE
#    -Isrc/
#    -lSDL2main 
#    -lSDL2)

