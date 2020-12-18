#include <string>
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
//#include <mesh.hpp>
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


    // On crée le VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // On le bind
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

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
        

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
