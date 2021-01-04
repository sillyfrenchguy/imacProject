#pragma once
#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <iostream>
#include "glimac/Program.hpp"
#include <string>



struct Vertex3DUV{
    public:
        glm::vec3 m_position;
        glm::vec3 m_color;
        glm::vec2 m_textCoordinates;
        Vertex3DUV():m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0,0,0)), m_textCoordinates(glm::vec2(0,0)){};
        Vertex3DUV(const glm::vec3 position, const glm::vec3 color, const glm::vec2 textCoordinates):m_position(position), m_color(color),m_textCoordinates(textCoordinates){};
        
};

class Interface{
    private :
        int m_currentHUD;
        
    public :
        static const int m_nbTexture = 12;
        GLuint VAO, VBO;
        GLuint Textures[m_nbTexture];

        Vertex3DUV vertices[6];
        glimac::Program shader;
        Interface();
        void drawInterface();
        int getCurrentHUD() const {return m_currentHUD;};
        void setCurrentHUD(int currentHUD){m_currentHUD = currentHUD;};
        void genInterface(int i);
};