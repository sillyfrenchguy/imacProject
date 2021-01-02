#include "glimac/common.hpp"
#include "scene.hpp"
#include <fstream>
#include <string>
#include "game.hpp"

namespace glimac{

//Constructeur
Scene::Scene(string path, Game &game):game(game){
    //m_camera(*this);
    this->loadScene(path);
}

//On charge la scène et ses attributs
void Scene::loadScene(string path){
    //On va parcourir le fichier de description de la scène et récupérer les données qui nous intéressent
    int nbModels;
    string modelName;
    string modelPath;
    float t_x, t_y, t_z, s_x, s_y, s_z;
    bool saber;

    ifstream fichier(path);
    if(fichier){
        string ligne;
        string word;

        while(getline(fichier, ligne)){
            //cout << ligne << endl;
            if(ligne.find("#")){
                istringstream iss(ligne);
                while(iss >> word >> nbModels){
                    cout << "Nombre de models : " << nbModels << endl;
                }
                getline(fichier, ligne);
                getline(fichier, ligne);

                for(int i =0; i<nbModels; i++){
                    istringstream iss(ligne);
                    while(iss >> modelName >> modelPath >> t_x >> t_y >> t_z >> s_x >> s_y >> s_z >> saber){
                        cout << "Nom du model : " << modelName << " Chemin : " << modelPath << " Light Saber : " << saber << endl;
                        //this->models[modelName] = Model("../project/template/models/testOBJ.obj");
                        this->models[modelName] = Model(modelPath, t_x, t_y, t_z, s_x, s_y, s_z, saber);
                    }
                    getline(fichier, ligne);
                }
            }
            
        }
    }
    else{
        cout << "Fichier illisible" << endl;
    }
    this->program = glimac::loadProgram("../project/template/shaders/3D.vs.glsl","../project/template/shaders/pointlights.fs.glsl");
	this->program.use();
    this->m_uMVPMatrix = glGetUniformLocation(this->program.getGLId(), "uMVPMatrix");
	this->m_uMVMatrix = glGetUniformLocation(this->program.getGLId(), "uMVMatrix");
	this->m_uNormalMatrix = glGetUniformLocation(this->program.getGLId(), "uNormalMatrix");

    this->m_uKd = glGetUniformLocation(this->program.getGLId(), "uKd");
    this->m_uKs = glGetUniformLocation(this->program.getGLId(), "uKs");
    this->m_uShininess = glGetUniformLocation(this->program.getGLId(), "uShininess");
    this->m_uLightDir_vs = glGetUniformLocation(this->program.getGLId(), "uLightDir_vs");
    this->m_uLightPos_vs = glGetUniformLocation(this->program.getGLId(), "uLightPos_vs");
    this->m_uLightIntensity = glGetUniformLocation(this->program.getGLId(), "uLightIntensity");

	//this->program = new glimac::Program(move(this->program));
}

//On dessine la scène dans la fenêtre
void Scene::drawScene(){
    this->program.use();
    this->m_ProjMatrix = glm::perspective(glm::radians(70.f), 1280.f/720.f, 0.1f, 2000.f);
    this->m_cameraViewMatrix = this->m_camera.getViewMatrix();
    this->m_earthMVMatrix = this->m_camera.getViewMatrix();
    
    glUniform3f(this->m_uKd, 1.0, 1.0, 1.0);
    glUniform3f(this->m_uKs, 1.0, 1.0, 1.0);
    glUniform1f(this->m_uShininess, 1.0);

    //LIGHT DIRECTIONAL
    //glm::vec4 LightDir = this->m_cameraViewMatrix * glm::vec4(1.0,1.0,1.0,0.);
    //glUniform3f(this->m_uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
    
    //LIGHT POINT
    glm::vec4 LightPoint = this->m_cameraViewMatrix * glm::vec4(1.0,1.0,1.0,0.);
    glUniform3f(this->m_uLightPos_vs, LightPoint.x, LightPoint.y, LightPoint.z);
    
    glUniform3f(this->m_uLightIntensity, 1.0, 1.0, 1.0); //j'ai mis 3 pour plus de luminosité

    //On parcourt la map contenant tous les models à l'aide d'un iterator
    map<string, Model>::iterator it_models;
    for(it_models = this->models.begin(); it_models != this->models.end(); it_models++){
        if (it_models->second.m_show == true){
            it_models->second.modelMatrix = this->m_earthMVMatrix;

            it_models->second.modelMatrix = glm::translate(it_models->second.modelMatrix, glm::vec3(it_models->second.t_x, it_models->second.t_y, it_models->second.t_z));

            //Les sabres tourneront sur eux-mêmes
            if(it_models->second.m_saber){
                it_models->second.m_rotation = it_models->second.m_rotation_velocity*this->game.getWindow().getTime();

                it_models->second.modelMatrix = glm::rotate(it_models->second.modelMatrix, it_models->second.m_rotation, glm::vec3(0,1,0));
            }

            it_models->second.modelMatrix = glm::scale(it_models->second.modelMatrix, glm::vec3(it_models->second.s_x, it_models->second.s_y, it_models->second.s_z));
            glUniformMatrix4fv(this->m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(it_models->second.modelMatrix));
            glUniformMatrix4fv(this->m_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(it_models->second.modelMatrix))));
            glUniformMatrix4fv(this->m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(m_ProjMatrix * it_models->second.modelMatrix));

            it_models->second.Draw(&this->program);

        }
    }
}
}