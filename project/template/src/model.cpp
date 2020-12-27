#include "Model.h"
#include "Mesh.h"
//#include <glimac/Image.hpp>


using namespace std;

// Définition du constructeur
Model::Model(GLchar *path){this->loadModel(path);};

void Model::Draw(Shader shader){
    for(GLuint i=0; i < this->meshes.size(); i++){
        this->meshes[i].Draw(shader);
    }
};

void Model::loadModel(string path){
    //On importe le model 3D avec Assimp, on procède à une triangulisation du model
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    //Vérification du chargement du model, si pb on affiche un message d'erreur
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }

    //On récupère le chemin complet du model
    this->directory = path.substr(0, path.find_last_of('/'));

    this->processNode(scene->mRootNode, scene);
};

//On traite chaque node et ses enfants de manière reccursive
void Model::processNode(aiNode *node, const aiScene *scene){
    for(GLuint i=0; i < node->mNumMeshes; i++){
        //La scène stocke toutes les relations entre les nodes
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(mesh, scene));
    }

    for(GLuint i = 0; i < node->mNumChildren; i++){
        this->processNode(node->mChildren[i], scene);
    }
};

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene){
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for(GLuint i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        //On stocke les données du vecteur assimp dans un vec3
        glm::vec3 vector;

        //Attributs de position
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        //Les normales
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        //Les coordonnées de texture
        if(mesh->mTextureCoords[0]){ //Si la mesh contient des coordonnées de textures on les récupère
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;

            vertex.TexCoords = vec;
        }
        else{
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for(GLuint i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];

        //On récupère les indices des vertex qui composent une face et on les stocke dans le vecteur d'indices
        for(GLuint j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }

    //On récupère les différents matériaux
    if(mesh->mMaterialIndex >= 0){
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        //ATTENTION CONVENTION: on part du principe que les textures diffuses auront une nomenclature de type "texture_diffuseN"

        vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return Mesh(vertices, indices, textures);
};

//Chargement des textures
vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName){
    vector<Texture> textures;

    for(GLuint i=0; i< mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);

        GLboolean skip = false;

        for(GLuint j = 0; j<textures_loaded.size(); j++){
            if(textures_loaded[j].path == str){
                textures.push_back(textures_loaded[j]);
                skip = true;
            }
        }
        //Si la texture n'a pas encore été chargée, on la charge
        if(!skip){
            Texture texture;
            texture.id = TextureFromFile( str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);

            this->textures_loaded.push_back(texture);
        }
    }
    return textures;
};

GLint Model::TextureFromFile(const char *path, string directory){
    string filename = string(path);
    filename = directory + '/' + filename;
    GLuint textureID;
    std::cout << "load texture " << filename << std::endl;
    glGenTextures(1, &textureID);
    auto image = glimac::ImageManager::loadImage(filename.c_str( ));

    //int width, height;
    //unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, textureID);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    std::cout << "texture ID " << textureID << std::endl;
    //SOIL_free_image_data(image);
    return textureID;
};
