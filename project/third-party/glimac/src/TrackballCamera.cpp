#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/TrackballCamera.hpp"

namespace glimac {
    // constructeur par défaut
    TrackballCamera::TrackballCamera():m_fDistance(5), m_fAngleX(0), m_fAngleY(0){};

    //constructeur 
    TrackballCamera::TrackballCamera(const float fDistance, const float fAngleX, const float fAngleY):m_fDistance(fDistance), m_fAngleX(fAngleX), m_fAngleY(fAngleY){};

    //destructeur
    TrackballCamera::~TrackballCamera(){};

    glm::mat4 TrackballCamera::getViewMatrix() const{
        glm::mat4 matrixMove = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -m_fDistance));
        glm::mat4 matrixRotateLeft = glm::rotate(glm::mat4(1.0), m_fAngleX, glm::vec3(1,0,0));
        glm::mat4 matrixRotateRight = glm::rotate(glm::mat4(1.0), m_fAngleY, glm::vec3(0,1,0));
        return matrixMove*matrixRotateLeft*matrixRotateRight;
    }; 

}

