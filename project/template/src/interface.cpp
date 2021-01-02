#include "interface.hpp"

using namespace glimac;

Interface::Interface(){
    //this->shader = Shader("../project/template/shaders/tex2D.vs.glsl", "../project/template/shaders/tex2D.fs.glsl");
    this->shader = loadProgram("../project/template/shaders/tex2D.vs.glsl","../project/template/shaders/tex2D.fs.glsl");

    this->vertices[0] = Vertex3DUV(glm::vec3(-1, -1, 0), glm::vec3(1,0,0), glm::vec2(0, 1));
    this->vertices[1] = Vertex3DUV(glm::vec3(1, -1, 0), glm::vec3(1,0,0), glm::vec2(1, 1));
    this->vertices[2] = Vertex3DUV(glm::vec3(0, 1, 0), glm::vec3(1,0,0), glm::vec2(0.5, 0));

    // On créé le VBO
    glGenBuffers(1, &this->VBO);

    // On le bind
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, (3) * sizeof(Vertex3DUV), this->vertices, GL_STATIC_DRAW);

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
    auto image = glimac::ImageManager::loadImage("/home/theo/TD_OPENGL/GLImac-Template/assets/textures/triforce.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
    

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Interface::drawInterface(SDLWindowManager* windowManager){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, this->Textures[0]);
    this->shader.use();
    //this->shader.Use();
    glBindVertexArray(this->VAO);
    
    
    
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    windowManager->swapBuffers();
}