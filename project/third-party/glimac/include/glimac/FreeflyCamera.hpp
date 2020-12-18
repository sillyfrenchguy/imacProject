#pragma once
#include "glimac/common.hpp"


namespace glimac {

class FreeflyCamera{
    private:
        glm::vec3 m_Position;
        float m_fPhi;
        float m_fTheta;

        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

        void computeDirectionVectors();


    public:
        //Constructeur
        FreeflyCamera();
        FreeflyCamera(const glm::vec3 Position, const float fPhi, const float fTheta);

        //destructeur
        ~FreeflyCamera();

        void moveLeft(float t){
            m_Position += t*m_LeftVector;
            computeDirectionVectors();
        };
        void moveFront(float t){
            m_Position += t*m_FrontVector;
            computeDirectionVectors();
        };
        void rotateLeft(float m_degrees){
            m_fPhi += glm::radians(m_degrees);
            computeDirectionVectors();
        };
        void rotateUp(float m_degrees){
            m_fTheta += glm::radians(m_degrees);
            computeDirectionVectors();
        };

        glm::mat4 getViewMatrix() const; 
};

};