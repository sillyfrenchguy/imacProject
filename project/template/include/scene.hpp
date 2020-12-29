#pragma once
#include "glimac/common.hpp"
#include "Model.h"

namespace glimac {

class Scene{
    private:
    map<string, Model> models;



    public:
        //Constructeur
        Scene(string path);

        //On charge la scène et ses attributs
        void loadScene(string path);

        //On dessine la scène dans la fenêtre
        void drawScene();

        //destructeur
        ~Scene();

    
};

};



