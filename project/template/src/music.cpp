#include "music.hpp"

void initMusicPlayer(){
    if(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        std::cout << Mix_GetError() << std::endl;
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}

Mix_Music* initSceneMusic(int scene){
    Mix_Music *musique;
    if(scene == 0){
        musique = Mix_LoadMUS("../project/assets/music/death_star_suite.mp3");
    }
    else{
        std::cout << "La scène ne contient pas de musique" << std::endl;
    }

    Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
    return musique;
}

void deleteSceneMusic(Mix_Music *musique){
    Mix_FreeMusic(musique);
}

void deleteMusicPlayer(){
    Mix_CloseAudio(); //Fermeture de l'API
}

