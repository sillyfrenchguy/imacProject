#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include "camera.hpp"
#include "game.hpp"
#include <iostream>

using namespace glimac;


int main(int, char** argv) {

    Game game(argv);

    glewExperimental = GL_TRUE;

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << "error de glew = " << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    game.init();
    game.loop();

    return EXIT_SUCCESS;
}
