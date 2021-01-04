#pragma once
#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "scene.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "music.hpp"
#include "interface.hpp"
#include "object.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

namespace glimac {
class Game{
    private:
        SDLWindowManager m_window;
        FilePath m_applicationPath;

        int m_current_scene;

    public:
        static const int m_nbScene = 2;
        Scene *m_scene[m_nbScene];
        Interface *interface;

        bool m_gameStart = false;
        bool m_gameLoading = true;
        bool m_infoBox = true;
        bool m_endGame = false;
        bool m_endMusic = true;
        bool m_interaction = false;

        Mix_Music *musique = NULL;
        Mix_Chunk *effetsSonores = NULL;
        
        //Constructeur
        Game(char** argv);

        //destructeur
        ~Game();

        //get de window
        SDLWindowManager& getWindow();

        void loop();

        // Fonction d'initialisation du jeu (préparation de la musique, 
        // chargement de la scène, lecture de la musique correspondant à la scène)
        void init();

        // Fonction pour afficher un écran de chargement : 
        // on créé une nouvelle interface, puis on dessine l'interface par défaut
        void loading();

        // Fonction de dessin qui se trouvera dans la boucle de rendu (on dessine la scène correspondante)
        void draw();

        // Fonction permettant le déplacement de la camera
        void moveCam(Camera *m_camera);

        // Fonction permettant au joueur d'attraper un sabre laser s'il est situé à proximité
        void catchObject(Saber *objet);

        // Fonction pour incrémenter le nombre de sabres récupérés dans la scène
        int addSaber();

        // On affiche l'ID de la scène courrante
        int getCurrentScene() const {return m_current_scene;}

        // On définit la scène courrante / le niveau du jeu
        void setCurrentScene(int current_scene){m_current_scene = current_scene;}

        void handleEvent(Camera* m_camera);

};
}



