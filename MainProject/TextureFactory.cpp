#include "stdafx.h"


TextureFactory::TextureFactory(){

    glGenTextures(1, &ground);
    glBindTexture(GL_TEXTURE_2D, ground);
    std::cout << ground << "is bound" << std::endl;
    int width, height;
    unsigned char* image = SOIL_load_image("textures\grass.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

}


GLint TextureFactory::getGround(){
    return ground;
}