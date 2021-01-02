#pragma once
#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <iostream>
#include "glimac/Program.hpp"
//#include "Shader.h"


struct Vertex3DUV{
    public:
        glm::vec3 m_position;
        glm::vec3 m_color;
        glm::vec2 m_textCoordinates;
        Vertex3DUV():m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0,0,0)), m_textCoordinates(glm::vec2(0,0)){};
        Vertex3DUV(const glm::vec3 position, const glm::vec3 color, const glm::vec2 textCoordinates):m_position(position), m_color(color),m_textCoordinates(textCoordinates){};
};

class Interface{
    public :
        GLuint VAO, VBO;
        GLuint Textures[1];

        Vertex3DUV vertices[3];
        //GLuint image;
        glimac::Program shader;
        Interface();
        void drawInterface();
};