#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
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
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/3D.vs.glsl",
        applicationPath.dirPath() + "shaders/directionallights.fs.glsl"
    );
    program.use();

    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
    GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
    GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
    GLint uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");


    // On crée une caméra de type Freefly
    FreeflyCamera newCamera;

    glEnable(GL_DEPTH_TEST);

    Sphere sphere(1, 32, 16);

    // On crée le VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // On le bind
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, (sphere.getVertexCount()) * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // on débind le VBO

    // On crée le VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // On bind le VAO
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION); //le 0 correspond à l'attribut de position

    const GLuint VERTEX_ATTR_NORMAL = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL); //le 1 correspond à l'attribut de normale

    //const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    //glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS); //le 1 correspond à l'attribut de texture

    // On bind le VBO sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // On indique le format de l'attribut de sommet position
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));
    //glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));
    
    // On débind le VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // On débind le VAO de la cible
    glBindVertexArray(0);

    // On crée un vecteur qui contient nos 32 axes de rotation différents
    std::vector<glm::vec3> randAxe;
    std::vector<glm::vec3> randTranslation;

    for(int i=0; i<32; i++){
        randAxe.push_back(glm::sphericalRand(1.0f));
        randTranslation.push_back(glm::sphericalRand(2.0f));
    }

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
        glBindVertexArray(vao);

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

        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

        glm::mat4 cameraViewMatrix = newCamera.getViewMatrix();

        glm::mat4 earthMVMatrix = glm::rotate(cameraViewMatrix, windowManager.getTime(), glm::vec3(0.0, 1.0, 0.0));
        
        glUniform3f(uKd, 0.4, 0.1, 0.8);
        glUniform3f(uKs, 0.5, 0.0, 0.0);
        glUniform1f(uShininess, 32.0);
        glm::vec4 LightDir = cameraViewMatrix*glm::vec4(1.0,1.0,1.0,0.);
        glUniform3f(uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform3f(uLightIntensity, 3.0,3.0,3.0);

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));    
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix*earthMVMatrix));

        
        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

        for(int i = 0; i <32; i++){
            glm::mat4 MVMatrix2 = newCamera.getViewMatrix();
            glm::mat4 NormalMatrix2 = glm::transpose(glm::inverse(MVMatrix2));
            MVMatrix2 = glm::rotate(MVMatrix2, windowManager.getTime(), randAxe[i]); // Translation * Rotation
            //MVMatrix2 = glm::translate(MVMatrix2, glm::vec3(0, 0, -5)); // Translation
            MVMatrix2 = glm::translate(MVMatrix2, randTranslation[i]); // Translation * Rotation * Translation
            MVMatrix2 = glm::scale(MVMatrix2, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale
            

            glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix2));
            glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix2));
            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix2));


            glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        }

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
