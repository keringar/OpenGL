#include <Util.h>
#include "Renderer/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <Renderer/stb_image.h>

//Constructor
Renderer::Renderer(const Window& window) : m_window{window} {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f); //Sky-Blue

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_MULTISAMPLE);
    //Create texture manager, shader manager and model manager
}

//Deconstructor
Renderer::~Renderer() {

    //Destroy texture, shader and model managers
}

//Copy constructor
Renderer::Renderer(const Renderer& render) : m_window{render.m_window} {

}

//Load all textures, models
bool Renderer::loadAll() {
    std::string vertexShader = File::readFile("shaders/basic.vert");
    std::string fragmentShader = File::readFile("shaders/basic.frag");

    m_shader.compile(vertexShader, fragmentShader);

    const int rows = 512;
    const int cols = 512;

    //Vertices
    std::vector<GLfloat> vertices;
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            //Vertices
            vertices.push_back((c - (cols/2)) / 5);
            vertices.push_back((r - (rows/2)) / 5);
            vertices.push_back(0.0);

            //Texture2D coords
            vertices.push_back((GLfloat)c / cols);
            vertices.push_back((GLfloat)c / cols);
        }
    }

    //Indices
    std::vector<GLuint> indices;
    for(GLuint r = 0; r < rows - 1; ++r){
        indices.push_back(r * cols);
        for(int c = 0; c < cols; ++c){
            indices.push_back(r * cols + c);
            indices.push_back((r + 1) * cols + c);
        }
        indices.push_back((r + 1) * cols + (cols - 1));
    }

    GLuint VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    size = indices.size();

    int x;
    int y;
    int comp;

    unsigned char* data = stbi_load("texture.jpg", &x, &y, &comp, STBI_rgb);

    m_texture = Texture2D();
    m_texture.upload(x, y, data);

    stbi_image_free(data);

    return true;
}

//Get render queue
void Renderer::submit() {

}

//Issue gpu commands
void Renderer::issueRenderCommands(glm::mat4 view) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.use();

    glm::mat4 model;
    m_shader.SetMatrix4("mvp", m_window.getProjectionMatrix((sin(glfwGetTime()) + 1) * 85.0f) * view * model);

    m_texture.bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    m_window.swap();
}

