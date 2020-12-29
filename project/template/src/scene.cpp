#pragma once
#include "glimac/common.hpp"
#include "scene.hpp"


//Constructeur
Scene::Scene(string path){
    this->loadScene(path);
};

//On charge la scène et ses attributs
void Scene::loadScene(string path){
    //On va parcourir le fichier de description de la scène et récupérer les données qui nous intéressent

};

//On dessine la scène dans la fenêtre
void Scene::drawScene();