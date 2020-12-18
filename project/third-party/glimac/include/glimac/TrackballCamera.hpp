#pragma once
#include "glimac/common.hpp"


namespace glimac {

class TrackballCamera{
    private:
        float m_fDistance;
        float m_fAngleX;
        float m_fAngleY;

    public:
        //Constructeur
        TrackballCamera();
        TrackballCamera(const float fDistance, const float fAngleX, const float fAngleY);

        //destructeur
        ~TrackballCamera();

        void moveFront(float m_delta){m_fDistance += m_delta;};
        void rotateLeft(float m_degrees){m_fAngleX += m_degrees/180 * M_PI;};
        void rotateRight(float m_degrees){m_fAngleY += m_degrees/180 * M_PI;};

        glm::mat4 getViewMatrix() const; 
};

};