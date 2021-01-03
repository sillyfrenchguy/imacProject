#include "object.hpp"
#include "game.hpp" 

namespace glimac{
	void Saber :: interact(Game* game){
		std::cout << "interact" << std::endl;
		game->catchObject(this); //As game is the class dealing with displaying the scene and couting sabers, it catches the objects
		
		delete this; //Then the saber is destroyed (not required anymore)
	}
	
	void Portal :: interact(Game* game){
		std::cout << "interact portal" << std::endl;
		if(game->m_scene[game->getCurrentScene()]->m_saber >= game->m_scene[game->getCurrentScene()]->m_total_saber){
			game->setCurrentScene(game->getCurrentScene() + 1);
		}
		
	}

	Saber::~Saber(){}
	Portal::~Portal(){}
}