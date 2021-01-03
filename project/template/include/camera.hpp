#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include "glimac/common.hpp"

namespace glimac {
class Camera{
    private:
        glm::vec3 m_Position;
        float m_fPhi;
        float m_fTheta;

        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

        // Méthode privée permettant de calculer les vecteurs Front, Left, Up à partir des coordonées sphériques (Theta et Pi)
        void computeDirectionVectors();


    public:
        // Constructeur par défaut de la caméra
        Camera();
        // Constructeur
        Camera(const glm::vec3 Position, const float fPhi, const float fTheta);

        // Destructeur
        ~Camera();

        void moveLeft(float t);
        void moveFront(float t);
        void rotateLeft(float m_degrees); 
        void rotateUp(float m_degrees);
        
        glm::mat4 getViewMatrix() const;
        
        // Pour récupérer la position de la camera sur les axes X et Z 
        glm::vec2 getPositionXZ() const;  
};
};



