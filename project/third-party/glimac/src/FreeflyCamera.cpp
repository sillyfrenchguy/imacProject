#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"

namespace glimac {
    // constructeur par défaut
    FreeflyCamera::FreeflyCamera():m_Position((0.f,0.f,0.f)), m_fPhi(M_PI), m_fTheta(0.f){computeDirectionVectors();};

    //constructeur 
    FreeflyCamera::FreeflyCamera(const glm::vec3 Position, const float fPhi, const float fTheta):m_Position(Position), m_fPhi(fPhi), m_fTheta(fTheta){computeDirectionVectors();};

    //destructeur
    FreeflyCamera::~FreeflyCamera(){};

    void FreeflyCamera::computeDirectionVectors(){
        m_FrontVector = glm::vec3(glm::cos(m_fTheta)*glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta)*glm::cos(m_fPhi)); 
        m_LeftVector = glm::vec3(glm::sin(m_fPhi + M_PI/2.0), 0, glm::cos(m_fPhi + M_PI/2.0)); 
        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }; 

    glm::mat4 FreeflyCamera::getViewMatrix() const{
        return glm::lookAt(m_Position, m_Position + m_FrontVector ,m_UpVector);
    }; 

}

