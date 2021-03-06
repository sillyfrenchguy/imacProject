cmake_minimum_required(VERSION 2.8)

set(OpenGL_GL_PREFERENCE "GLVND")

project(ImacGAME)

add_definitions(-std=c++11)

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(GLUT REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${SDLMIXER_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} third-party/glimac/include third-party/glm)

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${SDLMIXER_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} assimp)

add_subdirectory(third-party)

add_subdirectory(template)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
