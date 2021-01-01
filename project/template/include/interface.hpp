#pragma once
#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <iostream>
#include "glimac/Program.hpp"
//#include "Shader.h"


struct Vertex2DUV{
    public:
        glm::vec2 m_position;
        glm::vec2 m_textCoordinates;
        Vertex2DUV():m_position(glm::vec2(0,0)), m_textCoordinates(glm::vec2(0,0)){};
        Vertex2DUV(const glm::vec2 position, const glm::vec2 textCoordinates):m_position(position),m_textCoordinates(textCoordinates){};
};

class Interface{
    public :
        GLuint VAO, VBO;
        GLuint Textures[1];

        Vertex2DUV vertices[3];

        glimac::Program shader;
        Interface();
        void drawInterface(glimac::SDLWindowManager* windowManager);
};