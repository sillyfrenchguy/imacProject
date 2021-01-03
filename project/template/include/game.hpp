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
#include "object.hpp"

namespace glimac {
class Game{
    private:
        SDLWindowManager m_window;
        FilePath m_applicationPath;

        int m_current_scene;

    public:
        Scene *m_scene[2];
        Interface *interface;
        //int m_saber;
        bool m_gameStart = false;
        bool m_gameLoading = true;
        bool m_infoBox = true;
        
        //static const int m_total_saber = 4;
        //Constructeur
        Game(char** argv);

        //destructeur
        ~Game();

        //get de window
        SDLWindowManager& getWindow();

        void loop();

        void loading();

        // Fonction d'initialisation du jeu
        void init();

        // Fonction de dessin
        void draw();

        // Fonction permettant le déplacement de la camera
        void moveCam(Camera *m_camera);

        // Fonction permettant au joueur d'attraper un sabre laser s'il est situé à proximité
        void catchObject(Saber *objet);

        void displayImage();

        int addSaber();

        int getCurrentScene(){
            return m_current_scene;
        }

        void setCurrentScene(int current_scene){
            m_current_scene = current_scene;
        }

        void handleObject(Camera* m_camera);

};
}



