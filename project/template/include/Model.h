#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../third-party/glimac/include/glimac/Image.hpp"
//#include "../../third-party/SOIL2/SOIL2.h"
#include "Mesh.h"

using namespace std;


class Model
{
public:
    /*  Functions   */
    // Constructor, expects a filepath to a 3D model.
    Model( GLchar *path );

    // Draws the model, and thus all its meshes
    void Draw( Shader shader );

private:
    /*  Model Data  */
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

    /*  Functions   */
    // Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel( string path );

    // Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode( aiNode* node, const aiScene* scene );

    Mesh processMesh( aiMesh *mesh, const aiScene *scene );

    // Checks all material textures of a given type and loads the textures if they're not loaded yet.
    // The required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures( aiMaterial *mat, aiTextureType type, string typeName );

    GLint TextureFromFile( const char *path, string directory );
};