#include "interface.hpp"

using namespace glimac;

Interface::Interface(){
    //this->shader = Shader("../project/template/shaders/tex2D.vs.glsl", "../project/template/shaders/tex2D.fs.glsl");
    this->shader = loadProgram("../project/template/shaders/tex2D.vs.glsl","../project/template/shaders/tex2D.fs.glsl");

    this->vertices[0] = Vertex2DUV(glm::vec2(-1, -1),glm::vec2(0, 1));
    this->vertices[1] = Vertex2DUV(glm::vec2(1, -1),glm::vec2(1, 1));
    this->vertices[2] = Vertex2DUV(glm::vec2(0, 1),glm::vec2(0.5, 0));

    // On créé le VBO
    glGenBuffers(1, &this->VBO);

    // On le bind
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, (3) * sizeof(Vertex2DUV), this->vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, 0); // on débind le VBO

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION); //le 0 correspond à l'attribut de position

    const GLuint VERTEX_ATTR_TEXTURE = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE); //le 1 correspond à l'attribut de couleur

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GL_FLOAT), 0);
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GL_FLOAT), (const GLvoid*)(2*sizeof(GL_FLOAT)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &this->Textures[0]);
    std::unique_ptr<Image> image = loadImage("/home/theo/TD_OPENGL/GLImac-Template/assets/textures/triforce.png");
    glBindTexture(GL_TEXTURE_2D, this->Textures[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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