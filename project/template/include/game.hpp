#pragma once
#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "scene.hpp"
#include "Model.h"
#include "Shader.h"
#include "music.hpp"
#include "interface.hpp"

namespace glimac {
class Game{
    private:
        SDLWindowManager m_window;
        FilePath m_applicationPath;

    public:
        Scene *m_scene;
        Interface *interface;
        int m_saber;
        static const int m_total_saber = 3;
        //Constructeur
        Game(char** argv);

        //destructeur
        ~Game();

        //get de window
        SDLWindowManager& getWindow();

        void loop();

        // Fonction d'initialisation du jeu
        void init();

        // Fonction de dessin
        void draw();

        // Fonction permettant le déplacement de la camera
        void moveCam(Camera *m_camera);

        // Fonction permettant au joueur d'attraper un sabre laser s'il est situé à proximité
        void catchObject(Camera *m_camera);

        void displayImage();

        int addSaber();

};
}



