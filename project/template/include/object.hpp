#pragma once 
//#include "scene.hpp" 
#include "glimac/common.hpp" 
#include "model.hpp" 
//#include "game.hpp" 

namespace glimac{
	class Game;
	class Object { 

		public : 

			Model* m_model; 
			glm::vec2 m_position = {m_model->t_x, m_model->t_z}; 
			virtual void interact(Game* game){}; 

			Object(Model* model) : m_model(model){
				m_position.x = m_model->t_x;
				m_position.y = m_model->t_z;
			};

			virtual ~Object(){};
		
	};

	class Saber : public Object { //A saber is an object (daughter class)
		public : 

			Saber();
			Saber(Model* model) : Object(model){}; 
			~Saber();

			void interact(Game* game) override;

	};

	class Portal : public Object {
		public : 

			Portal();
			Portal(Model* model) : Object(model){}; 
			~Portal();

			void interact(Game* game) override;
	};
}