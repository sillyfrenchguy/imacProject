#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include "glimac/common.hpp"
//#include "camera.hpp"
#include "scene.hpp"
#include "Model.h"
#include "Shader.h"

namespace glimac {

class Game{
    private:
        //Camera m_camera;
        SDLWindowManager m_window;
        FilePath m_applicationPath;

        

        GLuint vao;
        GLuint vbo;

        /* Travail classe scène
        glm::mat4 m_ProjMatrix;
        glm::mat4 m_cameraViewMatrix;
        glm::mat4 m_earthMVMatrix;

        GLint m_uMVPMatrix;
        GLint m_uMVMatrix;
        GLint m_uNormalMatrix;

        GLint m_uKd;
        GLint m_uKs;
        GLint m_uShininess ;
        GLint m_uLightDir_vs ;
        GLint m_uLightIntensity;
        */

        std::vector<glm::vec3> m_randAxe;
        std::vector<glm::vec3> m_randTranslation;

        Model* model1;
        Model* model2;
        Model* model3;
		Program* program;

    public:
        Scene *m_scene;
        //Constructeur
        Game(char** argv);

        //destructeur
        ~Game();

        //get de window
        SDLWindowManager& getWindow();

        void loop();

        void init();

        //draw RENDERING
        void draw();

        //Event
        void moveCam(Camera *m_camera);
        void catchObject(Camera *m_camera);


};

}



