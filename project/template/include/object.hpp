#pragma once 
#include "scene.hpp"
#include "glimac/common.hpp"
#include "Model.h"


class Object {
	public : 
		Model* m_model;
		glm::vec2 position = {m_model->t_x, m_model->t_y};
		void interact(){};

		//Virtual class 
};

class Saber : public Object { //A saber is an object (daughter class)
	public : 

		Saber();
		Saber(Model model) : m_model(&model){}; // Error : Saber has no field named m_model ..? 
		~Saber();

		void interact();

};

class Portal : public Object {
	public : 

		Portal();
		Portal(Model model) : m_model(&model){}; // Error : Portal has no field named m_model ..? 
		~Portal();

		void interact();
};