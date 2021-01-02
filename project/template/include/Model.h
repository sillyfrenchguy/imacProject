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

#include "glimac/Image.hpp"
#include "glimac/Program.hpp"

#include "Mesh.h"

using namespace std;


GLint TextureFromFile( const char *path, string directory );


class Model
{
public:
    glm::mat4 modelMatrix;
    float t_x, t_y, t_z, s_x, s_y, s_z;
    bool m_show; 
    bool m_saber;
    bool m_saberCaught;
    float m_rotation;
    float m_rotation_velocity;	

    Model(){}

    Model(const Model &model){
        this->meshes = model.meshes;
        this->directory = model.directory;
        this->textures_loaded = model.textures_loaded;
        this->m_rotation = 0.0;
        this->m_rotation_velocity = 10.0;
    }
    
    Model(string path, float t_x, float t_y, float t_z, float s_x, float s_y, float s_z, bool saber)
    {
        this->t_x = t_x;
        this->t_y = t_y;
        this->t_z = t_z;
        this->s_x = s_x;
        this->s_y = s_y;
        this->s_z = s_z;
        this->m_show = true;
        this->m_saber = saber;
        this->m_saberCaught = false;   
        this->loadModel(path);
    }

    glm::vec2 getPositionXZ() const{
        return glm::vec2(t_x, t_z);
    }

    // Le destructeur
    ~Model() = default;

    void Draw( glimac::Program* shader )
    {
        for ( GLuint i = 0; i < this->meshes.size( ); i++ )
        {
            this->meshes[i].Draw( shader );
        }
    }

private:
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;
    

    void loadModel( string path )
    {
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
        //std::cout << this->directory << std::endl;

        this->processNode(scene->mRootNode, scene);
    }

    //On traite chaque node et ses enfants de manière reccursive
    void processNode( aiNode* node, const aiScene* scene ){
        for(GLuint i=0; i < node->mNumMeshes; i++){
            //La scène stocke toutes les relations entre les nodes
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            this->meshes.push_back(this->processMesh(mesh, scene));
        }

        for(GLuint i = 0; i < node->mNumChildren; i++){
            this->processNode(node->mChildren[i], scene);
        }
    }

    Mesh processMesh( aiMesh *mesh, const aiScene *scene )
    {
        // Data to fill
        vector<Vertex> vertices;
        vector<GLuint> indices;
        vector<Texture> textures;

        // Walk through each of the mesh's vertices
        for ( GLuint i = 0; i < mesh->mNumVertices; i++ ){
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
    }

    vector<Texture> loadMaterialTextures( aiMaterial *mat, aiTextureType type, string typeName )
    {
        vector<Texture> textures;

        for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            GLboolean skip = false;

            for ( GLuint j = 0; j < textures_loaded.size( ); j++ )
            {
                if( textures_loaded[j].path == str )
           {
                    textures.push_back( textures_loaded[j] );
                    skip = true;
                    break;
                }
            }

            if( !skip )
            {   
                Texture texture;
                texture.id = TextureFromFile( str.C_Str( ), this->directory );
                texture.type = typeName;
                texture.path = str;
                textures.push_back( texture );

                this->textures_loaded.push_back( texture );  
            }
        }

        return textures;
    }
};
