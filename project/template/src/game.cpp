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

		shader = new ::Shader( "../project/template/shaders/modelLoading.vs", "../project/template/shaders/modelLoading.frag" );

		ourModel = new Model("../project/template/models/nanosuit.obj");

        /*********************************
		 * HERE SHOULD COME THE INITIALIZATION CODE
		 *********************************/

		// On charge les shaders

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
		m_uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

		glEnable(GL_DEPTH_TEST);

		const GLuint VERTEX_ATTR_POSITION = 0;
		glEnableVertexAttribArray(VERTEX_ATTR_POSITION); //le 0 correspond à l'attribut de position

		const GLuint VERTEX_ATTR_NORMAL = 1;
		glEnableVertexAttribArray(VERTEX_ATTR_NORMAL); //le 1 correspond à l'attribut de normale

		const GLuint VERTEX_ATTR_TEXCOORDS = 2;
		glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS); //le 1 correspond à l'attribut de texture

		// On bind le VBO sur la cible
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// On indique le format de l'attribut de sommet position
		glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position));
		glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));
		glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));

		// On débind le VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// On débind le VAO de la cible
		glBindVertexArray(0);

		// On crée un vecteur qui contient nos 32 axes de rotation différents


		for(int i=0; i<32; i++){
			m_randAxe.push_back(glm::sphericalRand(1.0f));
			m_randTranslation.push_back(glm::sphericalRand(2.0f));
		}


    }


    //draw RENDERING
    void Game::draw(){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);

        m_camera.move();

        m_ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        m_cameraViewMatrix = m_camera.getViewMatrix();
        //m_earthMVMatrix = glm::rotate(m_cameraViewMatrix, m_window.getTime(), glm::vec3(0.0, 1.0, 0.0));
        m_earthMVMatrix = glm::scale(m_cameraViewMatrix, glm::vec3(0.2, 0.2, 0.2));


        glUniform3f(m_uKd, 0.5, 0.5, 0.5);
        glUniform3f(m_uKs, 0.5, 0.0, 0.0);
        glUniform1f(m_uShininess, 32.0);
        glm::vec4 LightDir = m_cameraViewMatrix*glm::vec4(1.0,1.0,1.0,0.);
        glUniform3f(m_uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform3f(m_uLightIntensity, 3.0,3.0,3.0);

        glUniformMatrix4fv(m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(m_earthMVMatrix));
        glUniformMatrix4fv(m_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(m_earthMVMatrix))));
        glUniformMatrix4fv(m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix*m_earthMVMatrix));


        // glDrawArrays(GL_TRIANGLES, 0, m_sphere.getVertexCount());
		ourModel->Draw(*shader);

		/*
        for(int i = 0; i <32; i++){
            glm::mat4 MVMatrix2 = m_camera.getViewMatrix();
            glm::mat4 NormalMatrix2 = glm::transpose(glm::inverse(MVMatrix2));
            // Translation * Rotation
            MVMatrix2 = glm::rotate(MVMatrix2, m_window.getTime(), m_randAxe[i]);
            //MVMatrix2 = glm::translate(MVMatrix2, glm::vec3(0, 0, -5)); // Translation
            MVMatrix2 = glm::translate(MVMatrix2, m_randTranslation[i]); // Translation * Rotation * Translation
            MVMatrix2 = glm::scale(MVMatrix2, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale


            glUniformMatrix4fv(m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix*MVMatrix2));
            glUniformMatrix4fv(m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix2));
            glUniformMatrix4fv(m_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix2));


            glDrawArrays(GL_TRIANGLES, 0, m_sphere.getVertexCount());
        }
		*/

        glBindVertexArray(0);

        // Update the display
        m_window.swapBuffers();
    }

}

/*
GLint TextureFromFile( const char *path, string directory )
{
    //Generate texture ID and load texture data
    string filename = string( path );
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures( 1, &textureID );

    //int width, height;

    // unsigned char *image = SOIL_load_image( filename.c_str( ), &width, &height, 0, SOIL_LOAD_RGB );
	//std::cout << "load texture " << filename << std::endl;
    //unique_ptr<glimac::Image> image = glimac::loadImage(filename.c_str());
    
	auto image = glimac::ImageManager::loadImage(filename.c_str( ));
    std::cout << "Pixels" << image->getPixels() << std::endl;
    
	if (!image) {
		std::cout << "failed to load texture " << filename << std::endl;
	}

    // Assign texture to ID
    glBindTexture( GL_TEXTURE_2D, textureID );
    //glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glGenerateMipmap( GL_TEXTURE_2D );

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture( GL_TEXTURE_2D, 0 );
    // SOIL_free_image_data( image );

    return textureID;
}
*/