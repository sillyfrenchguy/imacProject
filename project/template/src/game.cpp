#include "game.hpp"
#include <unistd.h>

namespace glimac {
    // Constructeur du jeu
    Game::Game(char** argv):m_scene(), m_window(1280, 720, "ImacGAME"), m_current_scene(0), m_applicationPath(argv[0]){}

    // Destructeur
    Game::~Game(){}

    // Fenêtre de jeu
    SDLWindowManager& Game::getWindow(){
        return m_window;
    }

    void Game::loop(){
        // Application loop:
        bool done = false;
        while(!done){
            // Event loop:
            SDL_Event e;
            while(m_window.pollEvent(e)) {
                switch (e.type){
                    case SDL_QUIT :
                        done = true; //lkeave the loop after this iteration

                    //case SDLK_e :
                        //handleObject(&((this->m_scene[this->getCurrentScene()])->m_camera));
                }
                // if(e.type == SDL_QUIT) {
                //     done = true; // Leave the loop after this iteration
                // }
                //if(this->getWindow().isKeyPressed(SDLK_p)){  
                   //this->setCurrentScene(1);
                //}
            }
            
            moveCam(&((this->m_scene[this->getCurrentScene()])->m_camera));
            //catchObject(&((this->m_scene[this->getCurrentScene()])->m_camera));
            handleObject(&((this->m_scene[this->getCurrentScene()])->m_camera));
            draw();
        }
    }

    // Fonction d'initialisation du jeu (préparation de la musique, chargement de la scène, lecture de la musique correspondant à la scène)
    void Game::init(){
        initMusicPlayer();
        Mix_Music *musique = initSceneMusic(0);
        loading();
        this->m_scene[0] = new Scene("../project/template/scenes/scene_0.txt", *this);
        this->m_scene[1] = new Scene("../project/template/scenes/scene_1.txt", *this);
        //musique = initSceneMusic(1);
        //this->m_scene[1] = new Scene("../project/template/scenes/sceneTest2.txt");
    }

    void Game::loading(){
        this->interface = new Interface();
		glEnable(GL_DEPTH_TEST); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->interface->drawInterface();
        m_window.swapBuffers();
    }

    // Fonction de dessin qui se trouvera dans la boucle de rendu (on dessine la scène correspondante)
    void Game::draw(){
        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        (this->m_scene[this->getCurrentScene()])->drawScene();
        this->interface->drawInterface();
        if(m_gameLoading){
            this->interface->setCurrentHUD(0);
            if(this->getWindow().isKeyPressed(SDLK_p)){
                
                this->interface->setCurrentHUD(1);
                Mix_Music *musique = initSceneMusic(0);
                musique = initSceneMusic(1);
                Mix_Chunk *r2d2 = initSounds(1);
                m_gameLoading = false;
            }
        }
        m_window.swapBuffers();
    }

    // Fonction permettant le déplacement de la camera
    void Game::moveCam(Camera *m_camera){
        float speed = 5.0;

        //Déplacement avec le clavier
        if(this->getWindow().isKeyPressed(SDLK_s)){
            
            m_camera->moveFront(-speed);
            cout << m_camera->getViewMatrix() << endl;
        }
        if(this->getWindow().isKeyPressed(SDLK_z)){
            m_camera->moveFront(speed);
        }
        if(this->getWindow().isKeyPressed(SDLK_q)){
            m_camera->moveLeft(speed);
        }
        if(this->getWindow().isKeyPressed(SDLK_d)){
            m_camera->moveLeft(-speed);
        }

        //Déplacement avec la souris
        glm::ivec2 mousePosition = glm::ivec2(0.0);

        if(this->getWindow().isMouseButtonPressed(SDL_BUTTON_LEFT)){
            mousePosition = this->getWindow().getMousePosition();
            float mousePositionX = mousePosition.x/1280.0f - 0.5;
            float mousePositionY = mousePosition.y/720.0f - 0.5;

            m_camera->rotateLeft(-3*mousePositionX);
            m_camera->rotateUp(-3*mousePositionY);
        }    
    }

    int Game::addSaber(){
        this->m_scene[this->getCurrentScene()]->m_saber += 1;
        if(this->m_scene[this->getCurrentScene()]->m_saber == this->m_scene[this->getCurrentScene()]->m_total_saber){
            std::cout << "Vous avez ramassé tous les sabres" << std::endl;
        }
        std::cout << this->m_scene[this->getCurrentScene()]->m_saber << std::endl;
        return this->m_scene[this->getCurrentScene()]->m_saber;
    }
    
    // Fonction permettant au joueur d'attraper un sabre laser s'il est situé à proximité
    /*
    void Game::catchObject(Camera *m_camera){ 
        //Capture avec le clavier
        if(this->getWindow().isKeyPressed(SDLK_e)){  
            map<string, Model>::iterator it_models;
            for(it_models = (this->m_scene[this->getCurrentScene()])->models.begin(); it_models != (this->m_scene[this->getCurrentScene()])->models.end(); it_models++){
                if (it_models->second.m_saber && glm::distance(it_models->second.getPositionXZ(), m_camera->getPositionXZ()) <=10.){
                    if(!it_models->second.m_saberCaught){
                        //std::cout << "Vous pouvez ramasser le sabre laser ! " << std::endl; 
                        it_models->second.m_show = false;
                        it_models->second.m_saberCaught = true;
                        Mix_Chunk *sonSabre = initSounds(0);
                        // on ajoute le sabre ramassé au score
                        
                        this->addSaber();
                    } 
                }
            } 
        }
    }*/
    void Game::catchObject(Saber *objet){
        std::cout << "Coucou je suis ton père" << std::endl;
        objet->m_model->m_show = false;
        objet->m_model->m_saberCaught = true;
        
        // Son de récupération du sabre
        Mix_Chunk *sonSabre = initSounds(0);
        
        // on ajoute le sabre ramassé au score 
        this->addSaber();
        
        // Mise à jour de l'interface de compte des sabres
        if(this->m_scene[this->getCurrentScene()]->m_saber == 1){
            this->interface->setCurrentHUD(4);
        }
        if(this->m_scene[this->getCurrentScene()]->m_saber == 2){
            this->interface->setCurrentHUD(5);
        }
        if(this->m_scene[this->getCurrentScene()]->m_saber == 3){
            this->interface->setCurrentHUD(6);
        }
        if(this->m_scene[this->getCurrentScene()]->m_saber == 4){
            this->interface->setCurrentHUD(7);
        }

    }

    void Game::handleObject(Camera *m_camera){      
        for (int i =0; i<this->m_scene[this->getCurrentScene()]->m_objects.size(); i++){  // Parcours les objets au lieu des modèles
            if (glm::distance((this->m_scene[this->getCurrentScene()]->m_objects[i]).m_position, m_camera->getPositionXZ()) <= 40.){ 
                if(!m_scene[m_current_scene]->m_objects[i].m_model->m_saberCaught){
                    // Affichage du message de proximité
                    this->interface->setCurrentHUD(2);
                    if(this->getWindow().isKeyPressed(SDLK_SPACE)){
                        std::cout << "Coucou key pressed" << std::endl;
                        m_scene[m_current_scene]->m_objects[i].interact(this); // Polymorphisme : Inutile de vérifier si c'est un sabre ou un portail    

                         m_scene[m_current_scene]->m_objects[i].m_model->m_show = false;
                         m_scene[m_current_scene]->m_objects[i].m_model->m_saberCaught = true;
                        
                        // Son de récupération du sabre
                        Mix_Chunk *sonSabre = initSounds(0);
                        
                        // on ajoute le sabre ramassé au score 
                        this->addSaber();
                        
                        // Mise à jour de l'interface de compte des sabres
                        if(this->m_scene[this->getCurrentScene()]->m_saber == 1){
                            this->interface->setCurrentHUD(4);
                        }
                        if(this->m_scene[this->getCurrentScene()]->m_saber == 2){
                            this->interface->setCurrentHUD(5);
                        }
                        if(this->m_scene[this->getCurrentScene()]->m_saber == 3){
                            this->interface->setCurrentHUD(6);
                        }
                        if(this->m_scene[this->getCurrentScene()]->m_saber == 4){
                            this->interface->setCurrentHUD(7);
                        }
                    }
                }
            }
        }

        // Condition affichage info box de début

        map<string, Model>::iterator it_portal;
        it_portal = this->m_scene[this->getCurrentScene()]->models.end();
        if(this->m_infoBox && glm::distance(it_portal->second.getPositionXZ(), m_camera->getPositionXZ()) >= 50.){
            this->interface->setCurrentHUD(3);
            this->m_infoBox = false;
        }

        // Tous les sabres ont été ramassés, message pour emprunter le portail
        if(glm::distance(it_portal->second.getPositionXZ(), m_camera->getPositionXZ()) <= 50. && this->m_scene[this->getCurrentScene()]->m_saber == this->m_scene[this->getCurrentScene()]->m_total_saber){
            this->interface->setCurrentHUD(9);
            if(this->getWindow().isKeyPressed(SDLK_k)){
                this->setCurrentScene(1);
            }
        }

    }
}


GLint TextureFromFile(const char *path, string directory){
    //On génère un ID pour la texture
    string filename = string( path );
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures( 1, &textureID );

    std::cout << "Chargement de la texture : " << filename << std::endl;
    auto image = glimac::ImageManager::loadImage(filename.c_str( ));
    if (!image) {
        std::cout << "Echec de chargement de la texture " << filename << std::endl;
    }

    // Association de la texture à l'ID
    glBindTexture( GL_TEXTURE_2D, textureID );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_FLOAT, image->getPixels() );
    glGenerateMipmap( GL_TEXTURE_2D );

    // Paramètres de placement de la texture
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture( GL_TEXTURE_2D, 0 );

    return textureID;
}


