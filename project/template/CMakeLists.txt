include_directories(include/)

file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)


set(EXECUTABLE "play")
add_executable(${EXECUTABLE} ${SRC_FILES} main.cpp)
target_link_libraries(${EXECUTABLE} ${ALL_LIBRARIES})


file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
