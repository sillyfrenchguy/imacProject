#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class mShader
{
    public:
        GLuint Program;
        mShader();
        mShader(const GLchar* vertexPath, const GLchar* fragmentPath);
        void Use();
};