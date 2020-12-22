#pragma once
#include "glimac/common.hpp"


namespace glimac {
class Game; 

class Camera{
    private:
        Game& game; 
        glm::vec3 m_Position;
        float m_fPhi;
        float m_fTheta;

        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

        void computeDirectionVectors();


    public:
        //Constructeur
        Camera(Game&);
        Camera(Game&, const glm::vec3 Position, const float fPhi, const float fTheta);

        //destructeur
        ~Camera();

        void moveLeft(float t);
        void moveFront(float t);
        void rotateLeft(float m_degrees); 
        void rotateUp(float m_degrees);
        glm::mat4 getViewMatrix() const;
        void move(); 
};

};


