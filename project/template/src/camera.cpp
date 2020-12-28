#include <cmath>
#include <vector>
#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include "glimac/common.hpp"
#include "camera.hpp"
#include "game.hpp"

namespace glimac {
    // constructeur par défaut
    Camera::Camera(Game& game)
    :game(game), m_Position((0.f,0.f,15.f)), m_fPhi(M_PI / 0.8), m_fTheta(-M_PI / 8) { computeDirectionVectors();};

    //constructeur
    Camera::Camera(Game& game, const glm::vec3 Position, const float fPhi, const float fTheta)
    :game(game), m_Position(Position), m_fPhi(fPhi), m_fTheta(fTheta){computeDirectionVectors();};

    //destructeur
    Camera::~Camera(){};

    void Camera::computeDirectionVectors(){
        m_FrontVector = glm::vec3(glm::cos(m_fTheta)*glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta)*glm::cos(m_fPhi));
        m_LeftVector = glm::vec3(glm::sin(m_fPhi + M_PI/2.0), 0, glm::cos(m_fPhi + M_PI/2.0));
        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    };

    glm::mat4 Camera::getViewMatrix() const{
        return glm::lookAt(m_Position, m_Position + m_FrontVector ,m_UpVector);
    };

    void Camera::moveLeft(float t){
            m_Position += t*m_LeftVector;
            computeDirectionVectors();
    }
    void Camera::moveFront(float t){
            m_Position += t*m_FrontVector;
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
    };



}
