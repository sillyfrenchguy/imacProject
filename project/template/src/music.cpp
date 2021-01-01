#include "music.hpp"

void initMusicPlayer(){
    if(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        std::cout << Mix_GetError() << std::endl;
    }
    Mix_AllocateChannels(2);
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

Mix_Chunk* initSounds(int event){
    Mix_Chunk *son;
    if(event == 0){
        son = Mix_LoadWAV("../project/assets/music/light_saber_sound.wav");
    }
    else{
        std::cout << "Le son n'existe pas" << std::endl;
    }

    Mix_PlayChannel(1, son, 0); //Jouer infiniment la musique
    return son;
}

void deleteSound(Mix_Chunk *son){
    Mix_FreeChunk(son);
}

void deleteSceneMusic(Mix_Music *musique){
    Mix_FreeMusic(musique);
}

void deleteMusicPlayer(){
    Mix_CloseAudio(); //Fermeture de l'API
}

