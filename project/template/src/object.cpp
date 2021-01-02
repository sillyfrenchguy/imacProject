#include "object.hpp"


void Saber :: interact(){
	Game :: catchObject(); //As game is the class dealing with displaying the scene and couting sabers, it catches the objects
	delete this; //Then the saber is destroyed (not required anymore)
}

void Portal :: interact(){
	game->m_current_scene ++;

}