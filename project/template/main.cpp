#include <string>
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "shader.hpp"
#include "freeFlyCamera.hpp"
#include "model.hpp"

#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <iostream>


using namespace glimac;


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "ImacGAME");

    glewExperimental = GL_TRUE;

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    
    // On charge les shaders
    mShader shader("shaders/modelLoading.vs.glsl", "shaders/modelLoading.fs.glsl");
    
    Model ourModel("./assets/models/nanosuit.obj");


    // On crée une caméra de type Freefly
    FreeflyCamera newCamera;

    glEnable(GL_DEPTH_TEST);



    /*********************************
     * NOTRE BOUCLE D'AFFICHAGE 
     *********************************/

    // Application loop:
    bool done = false;
    while(!done){

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }


        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(windowManager.isKeyPressed(SDLK_s)){
            newCamera.moveFront(-0.1);
        }
        if(windowManager.isKeyPressed(SDLK_z)){
            newCamera.moveFront(0.1);
        }
        if(windowManager.isKeyPressed(SDLK_q)){
            newCamera.moveLeft(0.1);
        }
        if(windowManager.isKeyPressed(SDLK_d)){
            newCamera.moveLeft(-0.1);
        }

        glm::ivec2 mousePosition = glm::ivec2(0.0);
        if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
            mousePosition = windowManager.getMousePosition();
            float mousePositionX = mousePosition.x/800.0f - 0.5;
            float mousePositionY = mousePosition.y/600.0f - 0.5;
            
            newCamera.rotateLeft(-3*mousePositionX);
            newCamera.rotateUp(-3*mousePositionY);
        }

        glm::mat4 projection = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
       
        glm::mat4 view = newCamera.getViewMatrix();
        
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); 
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ourModel.Draw(shader);

        
        

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
