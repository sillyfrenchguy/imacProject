#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include "glimac/common.hpp"
#include "mesh.hpp"


Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures):m_vertices(vertices), m_indices(indices), m_textures(textures)
{
    this->SetupMesh();
};

void Mesh::Draw(Shader shader){
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;

    for(GLuint i = 0; i < this->textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        stringstream ss;
        string number;
        string name = this->textures[i].type;

        // On vérifie le type de la texture 
        if("texture_diffuse" == name){
            ss << diffuseNr++;
        }
        else if("texture_specular" == name){
            ss << specularNr++;
        }
        // Stringstream : on convertit le nombre en string
        number = ss.str();

        // La variable uniforme est envoyée au shader
        glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i);

        //On bind la texture correspondant à la mesh
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }

    glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f;);

    glBindVertexArray(this.VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GLD_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    for(GLuint i = 0; i <this->textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

void Mesh::SetupMesh(){
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    // On lie le VBO et on recopie les vertices
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    // On lie l'EBO et on recopie les indices
    glBindBuffer(GL_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()*sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // Attribut de position
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);

    // Attribut de normale
    const GLuint VERTEX_ATTR_NORMAL = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Normal));

    // Attribut de texture
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
};