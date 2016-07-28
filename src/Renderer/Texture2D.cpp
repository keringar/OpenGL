#include "Renderer/Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <Renderer/stb_image.h>

Texture2D::Texture2D() :     Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT),
                             Wrap_T(GL_REPEAT), Filter_Min(GL_NEAREST), Filter_Max(GL_LINEAR) {

    glGenTextures(1, &ID);

}

void Texture2D::load(std::string path) {
    int x, y, comp;
    unsigned char* data = stbi_load(path.c_str(), &x, &y, &comp, STBI_rgb);

    upload((GLuint)x, (GLuint)y, data);

    stbi_image_free(data);
}

void Texture2D::upload(GLuint width, GLuint height, const unsigned char* data) {
    Width = width;
    Height = height;

    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);

    glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, ID);
}