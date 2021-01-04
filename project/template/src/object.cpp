#include "object.hpp"
#include "game.hpp" 

namespace glimac{
	void Saber :: interact(Game* game){
		game->catchObject(this); //As game is the class dealing with displaying the scene and couting sabers, it catches the objects


	}
	
	void Portal :: interact(Game* game){
		if(game->m_scene[game->getCurrentScene()]->m_saber >= game->m_scene[game->getCurrentScene()]->m_total_saber){
			//Affiche le HUD du portail
		    game->interface->setCurrentHUD(9);
	        // On joue le son du portail
	        game->effetsSonores = initSounds(2);

	        game->interface->setCurrentHUD(11);
	        try{
	        	if (game->getCurrentScene() + 1 > game->m_nbScene){
	        		throw int(1);
	        	}
	        	game->setCurrentScene(1);
	        }
	        catch (int i){
	        	std::cerr<<"ERROR : NEXT SCENE ("<<i<<") IS EMPTY - CHECK TXT FILE"<<std::endl;
	        }
		}
		
	}

	Saber::~Saber(){}
	Portal::~Portal(){}
}