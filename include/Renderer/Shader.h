#ifndef SHADER_H
#define SHADER_H

#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

class Shader {
    public:
        enum class ShaderType{
            SHADER,
            PROGRAM
        };

        Shader() { };
        operator GLuint() const {
            return ID;
        }

        void use();

        //Optional geometry shader, will be compiled if included
        void compile(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource = "");

        void SetFloat(const char* name, GLfloat value);
        void SetInteger(const char* name, GLint value);
        void SetVector2f(const char* name, GLfloat x, GLfloat y);
        void SetVector2f(const char* name, const glm::vec2& value);
        void SetVector3f(const char* name, GLfloat x, GLfloat y, GLfloat z);
        void SetVector3f(const char* name, const glm::vec3& value);
        void SetVector4f(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        void SetVector4f(const char* name, const glm::vec4& value);
        void SetMatrix4(const char* name, const glm::mat4& matrix);

    private:
        GLuint ID;
        std::unordered_map<const GLchar*, GLint> uniform_location_cache;

        void checkForErrors(GLuint obj, ShaderType type);

};

#endif