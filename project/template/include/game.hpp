#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include "glimac/common.hpp"
//#include "camera.hpp"
#include "scene.hpp"
#include "Model.h"
#include "Shader.h"
#include "music.hpp"

namespace glimac {

class Game{
    private:
        //Camera m_camera;
        SDLWindowManager m_window;
        FilePath m_applicationPath;
        
        GLuint vao;
        GLuint vbo;

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



