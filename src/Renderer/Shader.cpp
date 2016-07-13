#include <vector>
#include <Util.h>
#include "Renderer/Shader.h"

void Shader::use() {
    glUseProgram(ID);
}

void Shader::compile(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource) {
    GLuint vertex, fragment;
    GLuint geometry = 0;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    auto sourceString = vertexSource.c_str();
    glShaderSource(vertex, 1, &sourceString, nullptr);
    glCompileShader(vertex);
    checkForErrors(vertex, ShaderType::SHADER);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    sourceString = fragmentSource.c_str();
    glShaderSource(fragment, 1, &sourceString, nullptr);
    glCompileShader(fragment);
    checkForErrors(vertex, ShaderType::SHADER);

    if(geometrySource != "") {
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        sourceString = geometrySource.c_str();
        glShaderSource(geometry, 1, &sourceString, nullptr);
        glCompileShader(geometry);
        checkForErrors(geometry, ShaderType::SHADER);
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);

    if(geometry){
        glAttachShader(ID, geometry);
    }

    glLinkProgram(ID);
    checkForErrors(ID, ShaderType::PROGRAM);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometry) {
        glDeleteShader(geometry);
    }
}

void Shader::checkForErrors(GLuint obj, Shader::ShaderType type) {
    GLint success = 0;
    GLchar infoLog[1024];

    if(type == Shader::ShaderType::SHADER){
        glGetShaderiv(obj, GL_COMPILE_STATUS, &success);

        if(success == GL_FALSE){
            glGetShaderInfoLog(obj, 1024, nullptr, infoLog);
            Log::log("Shader Error: ");
            Log::log(infoLog, Log::Channels::None);
        }
    } else {
        glGetProgramiv(obj, GL_LINK_STATUS, &success);

        if(success == GL_FALSE){
            glGetProgramInfoLog(obj, 1024, nullptr, infoLog);
            Log::log("Shader Program Error: ");
            Log::log(infoLog, Log::Channels::None);
        }
    }
}

void Shader::SetFloat(const char* name, GLfloat value) {
    auto it = uniform_location_cache.find(name);

    if(it != uniform_location_cache.end()) {
        glUniform1f(it->second, value);
    } else {
        GLint uniformID = glGetUniformLocation(ID, name);
        uniform_location_cache.emplace(name, uniformID);
        glUniform1f(uniformID, value);
    }
}

void Shader::SetInteger(const char* name, GLint value) {
    auto it = uniform_location_cache.find(name);

    if(it != uniform_location_cache.end()) {
        glUniform1i(it->second, value);
    } else {
        GLint uniformID = glGetUniformLocation(ID, name);
        uniform_location_cache.emplace(name, uniformID);
        glUniform1i(uniformID, value);
    }
}

void Shader::SetVector2f(const char* name, GLfloat x, GLfloat y) {
    auto it = uniform_location_cache.find(name);

    if(it != uniform_location_cache.end()) {
        glUniform2f(it->second, x, y);
    } else {
        GLint uniformID = glGetUniformLocation(ID, name);
        uniform_location_cache.emplace(name, uniformID);
        glUniform2f(uniformID, x, y);
    }
}

void Shader::SetVector2f(const char* name, const glm::vec2& value) {
    auto it = uniform_location_cache.find(name);

    if(it != uniform_location_cache.end()) {
        glUniform2f(it->second, value.x, value.y);
    } else {
        GLint uniformID = glGetUniformLocation(ID, name);
        uniform_location_cache.emplace(name, uniformID);
        glUniform2f(uniformID, value.x, value.y);
    }
}

void Shader::SetVector3f(const char* name, GLfloat x, GLfloat y, GLfloat z) {
    auto it = uniform_location_cache.find(name);

    if(it != uniform_location_cache.end()) {
        glUniform3f(it->second, x, y, z);
    } else {
        GLint uniformID = glGetUniformLocation(ID, name);
        uniform_location_cache.emplace(name, uniformID);
        glUniform3f(uniformID, x, y, z);
    }
}

void Shader::SetVector3f(const char* name, const glm::vec3& value) {
    auto it = uniform_location_cache.find(name);

    if(it != uniform_location_cache.end()) {
        glUniform3f(it->second, value.x, value.y, value.z);
    } else {
        GLint uniformID = glGetUniformLocation(ID, name);
        uniform_location_cache.emplace(name, uniformID);
        glUniform3f(uniformID, value.x, value.y, value.z);
    }
}

void Shader::SetVector4f(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    auto it = uniform_location_cache.find(name);

    if(it != uniform_location_cache.end()) {
        glUniform4f(it->second, x, y, z, w);
    } else {
        GLint uniformID = glGetUniformLocation(ID, name);
        uniform_location_cache.emplace(name, uniformID);
        glUniform4f(uniformID, x, y, z, w);
    }
}

void Shader::SetVector4f(const char* name, const glm::vec4& value) {
    auto it = uniform_location_cache.find(name);

    if(it != uniform_location_cache.end()) {
        glUniform4f(it->second, value.x, value.y, value.z, value.w);
    } else {
        GLint uniformID = glGetUniformLocation(ID, name);
        uniform_location_cache.emplace(name, uniformID);
        glUniform4f(uniformID, value.x, value.y, value.z, value.w);
    }
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix) {
    auto it = uniform_location_cache.find(name);

    if(it != uniform_location_cache.end()) {
        glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(matrix));
    } else {
        GLint uniformID = glGetUniformLocation(ID, name);
        uniform_location_cache.emplace(name, uniformID);
        glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}