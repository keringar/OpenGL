#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>

class Texture2D {
    public:
        //Sets default options
        Texture2D();
        //Create and upload texture from byte array
        void upload(GLuint width, GLuint height, const unsigned char* data);
        //Use texture
        void bind() const;

        operator GLuint() const {
            return ID;
        }

        //Texture configuration options
        GLuint Width, Height;
        GLenum Internal_Format, Image_Format;
        GLint Wrap_S, Wrap_T;
        GLint Filter_Min, Filter_Max;

    private:
        GLuint ID;

};

#endif