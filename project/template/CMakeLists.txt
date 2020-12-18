include_directories(include/)

file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)


set(EXECUTABLE "play")
add_executable(${EXECUTABLE} ${SRC_FILE} main.cpp)
target_link_libraries(${EXECUTABLE} ${ALL_LIBRARIES})


file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
