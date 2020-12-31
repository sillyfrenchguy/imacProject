#include <cmath>
#include <vector>
#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include "glimac/common.hpp"
#include "camera.hpp"

namespace glimac {
    // constructeur par défaut
    //Camera::Camera(Game& game)
    //:game(game), m_Position((0.f,0.f,15.f)), m_fPhi(M_PI / 0.8), m_fTheta(-M_PI / 8) { computeDirectionVectors();};

    //constructeur
    //Camera::Camera(Game& game, const glm::vec3 Position, const float fPhi, const float fTheta)
    //:game(game), m_Position(Position), m_fPhi(fPhi), m_fTheta(fTheta){computeDirectionVectors();};

    Camera::Camera()
    :m_Position((0.f,1.f,15.f)), m_fPhi(M_PI / 0.8), m_fTheta(-M_PI / 8) { computeDirectionVectors();}

    //constructeur
    Camera::Camera(const glm::vec3 Position, const float fPhi, const float fTheta)
    :m_Position(Position), m_fPhi(fPhi), m_fTheta(fTheta){computeDirectionVectors();}

    //destructeur
    Camera::~Camera(){}

    void Camera::computeDirectionVectors(){
        m_FrontVector = glm::vec3(glm::cos(m_fTheta)*glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta)*glm::cos(m_fPhi));
        m_LeftVector = glm::vec3(glm::sin(m_fPhi + M_PI/2.0), 0, glm::cos(m_fPhi + M_PI/2.0));
        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }

    glm::mat4 Camera::getViewMatrix() const{
        return glm::lookAt(m_Position, m_Position + m_FrontVector ,m_UpVector);
    }

    glm::vec2 Camera::getPositionXZ() const{
        return glm::vec2(m_Position.x, m_Position.z);
    }

    void Camera::moveLeft(float t){
            m_Position += t*m_LeftVector;
            computeDirectionVectors();
    }
    void Camera::moveFront(float t){
            //m_Position += t*m_FrontVector;
            //La caméra ne peut pas se déplacer verticalement
            //On projette donc le front vector dans le plan, et pour que la vitesse ne soit pas affecté par l'angle Theta (angle avec l'horizon), 
            //on multiplie la norme du vecteur projeté par 1/(1 - sin(m_fTheta)**2) 
            m_Position.x += t*glm::l1Norm(m_FrontVector)*glm::cos(m_fTheta)*(1.0/(1-pow(glm::sin(m_fTheta),2)))*glm::sin(m_fPhi);
            m_Position.z += t*glm::l1Norm(m_FrontVector)*glm::cos(m_fTheta)*(1.0/(1-pow(glm::sin(m_fTheta),2)))*glm::cos(m_fPhi);
            computeDirectionVectors();  
    }
    void Camera::rotateLeft(float m_degrees){
            m_fPhi += glm::radians(m_degrees);
            computeDirectionVectors();
        }
    void Camera::rotateUp(float m_degrees){
        m_fTheta += glm::radians(m_degrees);
        computeDirectionVectors();
        }

    /*
    void Camera::move(){

		float speed = 0.5;

        //Déplacement avec le clavier
        if(game.getWindow().isKeyPressed(SDLK_s)){
            moveFront(-speed);
        }
        if(game.getWindow().isKeyPressed(SDLK_z)){
            moveFront(speed);
        }
        if(game.getWindow().isKeyPressed(SDLK_q)){
            moveLeft(speed);
        }
        if(game.getWindow().isKeyPressed(SDLK_d)){
            moveLeft(-speed);
        }

        //Déplacement avec la souris
        glm::ivec2 mousePosition = glm::ivec2(0.0);

        if(game.getWindow().isMouseButtonPressed(SDL_BUTTON_LEFT)){
            mousePosition = game.getWindow().getMousePosition();
            float mousePositionX = mousePosition.x/800.0f - 0.5;
            float mousePositionY = mousePosition.y/600.0f - 0.5;

            rotateLeft(-3*mousePositionX);
            rotateUp(-3*mousePositionY);
        }
    }*/



}
