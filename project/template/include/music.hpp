#pragma once

#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>



void initMusicPlayer();
Mix_Music* initSceneMusic(int scene);
void deleteSceneMusic(Mix_Music *musique);
void deleteMusicPlayer();