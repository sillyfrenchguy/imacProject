#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include "glimac/common.hpp"
#include "glimac/Program.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "model.hpp"
#include <vector>

namespace glimac{
class Game;
class Scene{
    private:

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
        GLint m_uLightPos_vs ;
        GLint m_uLightIntensity;



    public:
        map<string, Model> models;
        Game &game;

        int m_total_saber = 0;
        int m_saber = 0;
        
        Program program;
        Camera m_camera;
        std::vector<glimac::Object*> m_objects; 
        //Constructeur
        Scene(string path, Game &game);

        //On charge la scène et ses attributs
        void loadScene(string path);

        //On dessine la scène dans la fenêtre
        void drawScene();

        //destructeur
        ~Scene(){};


    
};
}




