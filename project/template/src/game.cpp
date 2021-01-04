#include "game.hpp"

namespace glimac {
    // Constructeur du jeu
    Game::Game(char** argv):m_scene(), m_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Star Wars : Portal Escape"), m_current_scene(0), m_applicationPath(argv[0]){}

    // Destructeur
    Game::~Game(){}

    // Fenêtre de jeu
    SDLWindowManager& Game::getWindow(){
        return m_window;
    }

    // Boucle de rendu et de gestion des évènements
    void Game::loop(){
        bool done = false;
        while(!done){
            SDL_Event e;
            while(m_window.pollEvent(e)) {
                switch (e.type){
                    case SDL_QUIT :
                        done = true; // Pour quitter la boucle lorsque le joueur ferme le jeu
                        break;

                    case SDL_KEYUP : 
                        m_interaction = false;
                        break;

                    // case SDL_MOUSEBUTTONDOWN : //POUR POSITIONNEMENT SABRE A DELETE
                    //     std::cout<<((this->m_scene[this->getCurrentScene()])->m_camera).getPositionXZ() << std::endl;
                }
            }
            if(this->getWindow().isKeyPressed(SDLK_SPACE) || this->getWindow().isKeyPressed(SDLK_k)){  
               m_interaction = true;
            }
            moveCam(&((this->m_scene[this->getCurrentScene()])->m_camera));
            //catchObject(&((this->m_scene[this->getCurrentScene()])->m_camera));
            handleEvent(&((this->m_scene[this->getCurrentScene()])->m_camera));
            draw();
            SDL_Delay(30);
        }
        // A la fermeture du jeu, on libère la mémoire allouée à la musique et aux bruitages
        deleteSceneMusic(this->musique);
        deleteSound(this->effetsSonores);
        deleteMusicPlayer();
        this->~Game();
        
    }

    // Fonction d'initialisation du jeu (préparation de la musique, chargement de la scène, lecture de la musique correspondant à la scène)
    void Game::init(){
        initMusicPlayer();
        this->musique = initSceneMusic(0);
        loading();

        // Chargement des modèles des deux scènes sans les afficher/dessiner
       // Concrétement on lit les fichiers de description de scènes puis on stocke les modèles et leurs informations
        this->m_scene[0] = new Scene("../project/template/scenes/scene_0.txt", *this);
        this->m_scene[1] = new Scene("../project/template/scenes/scene_1.txt", *this);
    }
    
    // Fonction pour afficher un écran de chargement : on créé une nouvelle interface, puis on dessine l'interface par défaut
    void Game::loading(){
        this->interface = new Interface();
		glEnable(GL_DEPTH_TEST); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->interface->drawInterface();
        m_window.swapBuffers();
    }

    // Fonction de dessin qui se trouvera dans la boucle de rendu (on dessine la scène correspondante)
    void Game::draw(){
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // On dessine la scène courrante du jeu
        (this->m_scene[this->getCurrentScene()])->drawScene();

        // On dessine le HUD associé à la scène
        this->interface->drawInterface();

        // Si le jeu a fini de charger :
        if(this->m_gameLoading){
            // On affiche le menu
            this->interface->setCurrentHUD(0);

            // Si on lance le jeu en cliquant sur "P"
            if(this->getWindow().isKeyPressed(SDLK_p)){
                // On affiche le HUD de description de l'histoire
                this->interface->setCurrentHUD(1);

                // On lance la musique associée à la scène
                this->musique = initSceneMusic(1);

                // On les bruitages de R2-D2
                this->effetsSonores = initSounds(1);

                this->m_gameLoading = false;
            }
        }
        // Si le jeu est terminé, on lance la musique de fin
        if(this->m_endGame){
            this->musique = initSceneMusic(2);
            this->m_endGame = false;
        }
        m_window.swapBuffers();
    }

    // Fonction permettant le déplacement de la camera
    void Game::moveCam(Camera *m_camera){
        float speed = 5.0;

        //Déplacement avec le clavier
        if(this->getWindow().isKeyPressed(SDLK_s)){
            
            m_camera->moveFront(-speed);
            
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
            float mousePositionX = mousePosition.x/(float)SCREEN_WIDTH - 0.5;
            float mousePositionY = mousePosition.y/(float)SCREEN_HEIGHT- 0.5;

            m_camera->rotateLeft(-3*mousePositionX);
            m_camera->rotateUp(-3*mousePositionY);
        }    
    }

    // Fonction pour incrémenter le nombre de sabres récupérés dans la scène
    int Game::addSaber(){
        this->m_scene[this->getCurrentScene()]->m_saber += 1;
        return this->m_scene[this->getCurrentScene()]->m_saber;
    }
    
    // Fonction permettant au joueur d'attraper un sabre laser s'il est situé à proximité

    void Game::catchObject(Saber *objet){
        objet->m_model->m_show = false;
        objet->m_model->m_saberCaught = true;
        
        // Son de récupération du sabre
       this->effetsSonores = initSounds(0);
        
        // on ajoute le sabre ramassé au score 
        this->addSaber();
        
        // Mise à jour de l'interface de compte des sabres

        switch (this->m_scene[this->getCurrentScene()]->m_saber){
            case 1 :
                this->interface->setCurrentHUD(4);
                break;

            case 2 : 
                this->interface->setCurrentHUD(5);
                break;

            case 3 :
                this->interface->setCurrentHUD(6);
                break;

            case 4 :
                this->interface->setCurrentHUD(7);
                break;

        }


    }

    void Game::handleEvent(Camera *m_camera){      
        for (int i =0; i<this->m_scene[this->getCurrentScene()]->m_objects.size(); i++){  // Parcours les objets au lieu des modèles
            if (glm::distance((this->m_scene[this->getCurrentScene()]->m_objects[i])->m_position, m_camera->getPositionXZ()) <= 40.){ 
                if(!m_scene[m_current_scene]->m_objects[i]->m_model->m_saberCaught){
                    // Affichage du message de proximité
                    if (this->m_scene[this->getCurrentScene()]->m_objects[i]->m_model->m_saber) {
                        this->interface->setCurrentHUD(2);
                    }
                    else if (this->m_scene[this->getCurrentScene()]->m_saber >= this->m_scene[this->getCurrentScene()]->m_total_saber){
                        this->interface->setCurrentHUD(9);
                    }
                    
                    if(m_interaction){
                        m_scene[m_current_scene]->m_objects[i]->interact(this); 
                        
                    }

                }
            }
        }
        // Si on se trouve au niveau final
        if(this->getCurrentScene() == 1){
            if(m_camera->getPositionXZ().x >= 800. && this->m_endMusic){
                this->interface->setCurrentHUD(10);
                this->m_endGame = true;
                this->m_endMusic = false;
                
            }
        }
        // Si on se trouve dans un labyrinthe
        else if(this->getCurrentScene() == 0){
            // Condition affichage info box de début
            map<string, Model>::iterator it_portal;
            it_portal = this->m_scene[this->getCurrentScene()]->models.end();
            if(this->m_infoBox && glm::distance(it_portal->second.getPositionXZ(), m_camera->getPositionXZ()) >= 50.){
                this->interface->setCurrentHUD(3);
                this->m_infoBox = false;
            }

        }   
    }
}


GLint TextureFromFile(const char *path, string directory){
    //On génère un ID pour la texture
    string filename = string( path );
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures(1, &textureID);

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


