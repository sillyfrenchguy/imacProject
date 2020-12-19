#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture{
    GLuint id;
    string type;
    aiString path;
};

class Mesh{
    public:
        vector<Vertex> m_vertices;
        vector<GLuint> m_indices;
        vector<Texture> m_textures;
        
        //Constructeur
        Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

        //Destructeur
        //~Mesh();

        void Draw(mShader shader);

    private:
        GLuint VAO, VBO, EBO;

        void SetupMesh();
};

