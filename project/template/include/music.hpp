#pragma once
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void initMusicPlayer();
Mix_Music* initSceneMusic(int scene);
Mix_Chunk* initSounds(int event);
void deleteSceneMusic(Mix_Music *musique);
void deleteSound(Mix_Chunk *son);
void deleteMusicPlayer();