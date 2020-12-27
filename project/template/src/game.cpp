#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include "glimac/common.hpp"
#include "game.hpp"

namespace glimac {
    /*constructeur*/
    Game::Game(char** argv) :
    // On créé une camera
    m_camera(*this),
    // Initialize SDL and open a window
    m_window(800, 600, "ImacGAME"),

    m_applicationPath(argv[0])

    {}


    //destructeur
    Game::~Game(){};


    //get window
    SDLWindowManager& Game::getWindow(){
        return m_window;
    }


    void Game::loop(){

        /*BOUCLE D'AFFICHAGE*/

        // Application loop:
        bool done = false;
        while(!done){

            // Event loop:
            SDL_Event e;

            while(m_window.pollEvent(e)) {
                if(e.type == SDL_QUIT) {
                    done = true; // Leave the loop after this iteration
                }
            }

            draw();
        }
    }





    void Game::init(){
        glEnable(GL_DEPTH_TEST);

        // Chargement et compilation des shaders
		shader = new ::Shader( "../project/template/shaders/modelLoading.vs", "../project/template/shaders/modelLoading.frag" );

        //Chargement des objets
		ourModel = new Model("../project/template/models/nanosuit.obj");
        //ourModel = new Model("../project/template/models/Corridor_Left.obj");
        m_ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);

        /*********************************
		 * HERE SHOULD COME THE INITIALIZATION CODE
		 *********************************/
        
		// On charge les shaders
        /*
		Program program = loadProgram(
			m_applicationPath.dirPath() + "shaders/3D.vs.glsl",
			m_applicationPath.dirPath() + "shaders/directionallights.fs.glsl"
		);
		program.use();

		m_uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
		m_uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
		m_uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    
		m_uKd = glGetUniformLocation(program.getGLId(), "uKd");
		m_uKs = glGetUniformLocation(program.getGLId(), "uKs");
		m_uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
		m_uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
		m_uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");*/
        

        /*
		const GLuint VERTEX_ATTR_POSITION = 0;
		glEnableVertexAttribArray(VERTEX_ATTR_POSITION); //le 0 correspond à l'attribut de position

		const GLuint VERTEX_ATTR_NORMAL = 1;
		glEnableVertexAttribArray(VERTEX_ATTR_NORMAL); //le 1 correspond à l'attribut de normale

		const GLuint VERTEX_ATTR_TEXCOORDS = 2;
		glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS); //le 1 correspond à l'attribut de texture

        

		// On indique le format de l'attribut de sommet position
		glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position));
		glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));
		glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));

		// On débind le VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// On débind le VAO de la cible
		glBindVertexArray(0);*/
        
    }


    //draw RENDERING
    void Game::draw(){
        m_camera.move();

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->Use();

        m_cameraViewMatrix = m_camera.getViewMatrix();
        std::cout << m_cameraViewMatrix << std::endl;

        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(m_ProjMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(m_cameraViewMatrix));
        
        glm::mat4 model = glm::mat4(0.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ourModel->Draw(*shader);

        // Update the display
        m_window.swapBuffers();
    }

}