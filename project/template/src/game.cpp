#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include "glimac/common.hpp"
#include "game.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace glimac {
    /*constructeur*/
    Game::Game(char** argv) :
    // On créé une camera
    //m_camera(*this),
    // Initialize SDL and open a window
    m_scene(),
    m_window(1000, 800, "ImacGAME"),
    m_applicationPath(argv[0])
    {}

    //destructeur
    Game::~Game(){}

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
        this->m_scene= new Scene("../project/template/scenes/sceneTest.txt");
        
        /*
		model1 = new Model("../project/template/models/testOBJ.obj");
		model2 = new Model("../project/template/models/iPhone5/iPhone5.obj");
		model3 = new Model("../project/template/models/sdcard/SD_Card.obj");

		// On charge les shaders
		Program program = loadProgram(
			"../project/template/shaders/3D.vs.glsl",
			"../project/template/shaders/directionallights.fs.glsl"
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

		this->program = new Program(std::move(program));*/

		glEnable(GL_DEPTH_TEST);
    }

    //draw RENDERING
    void Game::draw(){

        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        this->m_scene->drawScene();
        /*
        m_camera.move();

        m_ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 2000.f);
        m_cameraViewMatrix = m_camera.getViewMatrix();
		//m_earthMVMatrix = glm::rotate(m_cameraViewMatrix, m_window.getTime(), glm::vec3(0.0, 1.0, 0.0));
        m_earthMVMatrix = m_camera.getViewMatrix();

        glUniform3f(m_uKd, 1.0, 1.0, 1.0);
        glUniform3f(m_uKs, 1.0, 1.0, 1.0);
        glUniform1f(m_uShininess, 1.0);
        glm::vec4 LightDir = m_cameraViewMatrix * glm::vec4(1.0,1.0,1.0,0.);
        glUniform3f(m_uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform3f(m_uLightIntensity, 1.0,1.0,1.0);

        glUniformMatrix4fv(m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(m_earthMVMatrix));
        glUniformMatrix4fv(m_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(m_earthMVMatrix))));
        glUniformMatrix4fv(m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix * m_earthMVMatrix));

		model1->Draw(program);

		glm::mat4 iPhoneMatrix = m_earthMVMatrix;
		iPhoneMatrix = glm::translate(iPhoneMatrix, glm::vec3(0,10,-10));
		iPhoneMatrix = glm::scale(iPhoneMatrix, glm::vec3(0.02f, 0.02f, 0.02f));
        glUniformMatrix4fv(m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(iPhoneMatrix));
        glUniformMatrix4fv(m_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(iPhoneMatrix))));
        glUniformMatrix4fv(m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix * iPhoneMatrix));

		model2->Draw(program);

		glm::mat4 sdcardMatrix = m_earthMVMatrix;
		sdcardMatrix = glm::translate(sdcardMatrix, glm::vec3(0,-100,15));
		sdcardMatrix = glm::scale(sdcardMatrix, glm::vec3(5.f, 5.f, 5.f));
        glUniformMatrix4fv(m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(sdcardMatrix));
        glUniformMatrix4fv(m_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(sdcardMatrix))));
        glUniformMatrix4fv(m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix * sdcardMatrix));

		model3->Draw(program);
        */
        m_window.swapBuffers();
    }
}


GLint TextureFromFile( const char *path, string directory )
{
    //Generate texture ID and load texture data
    string filename = string( path );
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures( 1, &textureID );

    // unsigned char *image = SOIL_load_image( filename.c_str( ), &width, &height, 0, SOIL_LOAD_RGB );
	std::cout << "load texture " << filename << std::endl;
	auto image = glimac::ImageManager::loadImage(filename.c_str( ));
	if (!image) {
		std::cout << "failed to load texture " << filename << std::endl;
	}

    // Assign texture to ID
    glBindTexture( GL_TEXTURE_2D, textureID );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_FLOAT, image->getPixels() );
    glGenerateMipmap( GL_TEXTURE_2D );

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture( GL_TEXTURE_2D, 0 );
    // SOIL_free_image_data( image );

    return textureID;
}
