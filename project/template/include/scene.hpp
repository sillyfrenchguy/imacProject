#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include "glimac/common.hpp"
#include "glimac/Program.hpp"
#include "camera.hpp"
#include "Model.h"

class Scene{
    private:
        
        //map<string, Model> models;

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
        
        glimac::Program program;
        glimac::Camera m_camera;
        //Constructeur
        Scene(){};
        Scene(string path);

        //On charge la scène et ses attributs
        void loadScene(string path);

        //On dessine la scène dans la fenêtre
        void drawScene();

        //destructeur
        //~Scene();
        //glimac::Camera getCam(){return this->m_camera;} ;

    
};




