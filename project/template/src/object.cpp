#include "object.hpp"

namespace glimac{
	void Saber :: interact(Game* game){
		game->catchObject(&((game->m_scene[game->getCurrentScene()])->m_camera)); //As game is the class dealing with displaying the scene and couting sabers, it catches the objects
		
		delete this; //Then the saber is destroyed (not required anymore)
	}

	void Portal :: interact(Game* game){
		if(game->m_saber >= 4){
			game->setCurrentScene(game->getCurrentScene() + 1);
		}
		
	}

	Saber::~Saber(){}
	Portal::~Portal(){}
}