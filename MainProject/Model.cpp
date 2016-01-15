#include "stdafx.h"
#include "Model.h"

Model::Model(){

}


void Model::makeTexture() {
    glGenTextures(1, &this->tid);

    glBindTexture(GL_TEXTURE_2D, this->tid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    unsigned char* image = SOIL_load_image("reap/predator.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Model::initialize(){
    makeTexture();
	for (unsigned int i = 0; i < this->components.size(); i++) {
        this->components[i]->init();
    }

}


void Model::draw(){
	for (unsigned int i = 0; i < this->components.size(); i++) {
        this->components[i]->draw();
    }
}