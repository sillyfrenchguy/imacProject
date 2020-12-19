#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.hpp"
#include <glimac/Image.hpp>

using namespace std;

GLint TextureFromFile(const char *path, string directory);

class Model{
    public:
        //Constructeur
        Model(const GLchar *path);

        //Destructeur
        //~Model();

        //Méthode permettant de dessiner chaque mesh du model 3D
        void Draw(mShader shader);

    private:
        vector<Mesh> meshes;
        string directory;
        vector<Texture> texture_loaded;

        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiNode *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

};
