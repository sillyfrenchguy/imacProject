#include "interface.hpp"

using namespace glimac;

Interface::Interface():m_currentHUD(8){
    //this->shader = Shader("../project/template/shaders/tex2D.vs.glsl", "../project/template/shaders/tex2D.fs.glsl");
    this->shader = loadProgram("../project/template/shaders/tex2D.vs.glsl","../project/template/shaders/tex2D.fs.glsl");

    this->vertices[0] = Vertex3DUV(glm::vec3(-1.0, -1.0, 0), glm::vec3(1,0,0), glm::vec2(0, 1));
    this->vertices[1] = Vertex3DUV(glm::vec3(1.0, -1.0, 0), glm::vec3(1,0,0), glm::vec2(1, 1));
    this->vertices[2] = Vertex3DUV(glm::vec3(1.0, 1.0, 0), glm::vec3(1,0,0), glm::vec2(1, 0));
    this->vertices[3] = Vertex3DUV(glm::vec3(-1.0, -1.0, 0), glm::vec3(1,0,0), glm::vec2(-1, 0));
    this->vertices[4] = Vertex3DUV(glm::vec3(-1.0, 1.0, 0), glm::vec3(1,0,0), glm::vec2(-1, -1));
    this->vertices[5] = Vertex3DUV(glm::vec3(1.0, 1.0, 0), glm::vec3(1,0,0), glm::vec2(0, -1));

    // On créé le VBO
    glGenBuffers(1, &this->VBO);

    // On le bind
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, (6) * sizeof(Vertex3DUV), this->vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, 0); // on débind le VBO

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION); //le 0 correspond à l'attribut de position

    const GLuint VERTEX_ATTR_COLOR = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR); //le 1 correspond à l'attribut de couleur

    const GLuint VERTEX_ATTR_TEXTURE = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE); //le 2 correspond à l'attribut de texture

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), 0);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (const GLvoid*)(3*sizeof(GL_FLOAT)));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (const GLvoid*)(6*sizeof(GL_FLOAT)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &this->Textures[0]);
    auto image = glimac::ImageManager::loadImageAlpha("../project/assets/img/menu_chargement.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[1]);
    auto infoBox1 = glimac::ImageManager::loadImageAlpha("../project/assets/img/info_r2.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, infoBox1->getWidth(), infoBox1->getHeight(), 0, GL_RGBA, GL_FLOAT, infoBox1->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[2]);
    auto recupSabre = glimac::ImageManager::loadImageAlpha("../project/assets/img/info_box.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, recupSabre->getWidth(), recupSabre->getHeight(), 0, GL_RGBA, GL_FLOAT, recupSabre->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[3]);
    auto saberCount0 = glimac::ImageManager::loadImageAlpha("../project/assets/img/saber_count_0.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, saberCount0->getWidth(), saberCount0->getHeight(), 0, GL_RGBA, GL_FLOAT, saberCount0->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[4]);
    auto saberCount1 = glimac::ImageManager::loadImageAlpha("../project/assets/img/saber_count_1.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, saberCount1->getWidth(), saberCount1->getHeight(), 0, GL_RGBA, GL_FLOAT, saberCount1->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[5]);
    auto saberCount2 = glimac::ImageManager::loadImageAlpha("../project/assets/img/saber_count_2.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, saberCount2->getWidth(), saberCount2->getHeight(), 0, GL_RGBA, GL_FLOAT, saberCount2->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[6]);
    auto saberCount3 = glimac::ImageManager::loadImageAlpha("../project/assets/img/saber_count_3.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[6]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, saberCount3->getWidth(), saberCount3->getHeight(), 0, GL_RGBA, GL_FLOAT, saberCount3->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[7]);
    auto saberCount4 = glimac::ImageManager::loadImageAlpha("../project/assets/img/saber_count_4.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[7]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, saberCount4->getWidth(), saberCount4->getHeight(), 0, GL_RGBA, GL_FLOAT, saberCount4->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[8]);
    auto loading = glimac::ImageManager::loadImageAlpha("../project/assets/img/a_long_time_ago.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[8]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loading->getWidth(), loading->getHeight(), 0, GL_RGBA, GL_FLOAT, loading->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[9]);
    auto portail = glimac::ImageManager::loadImageAlpha("../project/assets/img/info_portail.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[9]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, portail->getWidth(), portail->getHeight(), 0, GL_RGBA, GL_FLOAT, portail->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &this->Textures[10]);
    auto fin = glimac::ImageManager::loadImageAlpha("../project/assets/img/ecran_de_fin.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[10]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fin->getWidth(), fin->getHeight(), 0, GL_RGBA, GL_FLOAT, fin->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Interface::drawInterface(){
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    this->shader.use();
    glBindVertexArray(this->VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->Textures[this->m_currentHUD]);
    glUniform1i(glGetUniformLocation(this->shader.getGLId(), "vTexture"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}