#include "main.h"
#include <tinygl/tinygl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fmt/format.h>
#include <iostream>

std::string resourcePath(const std::string& resource)
{
    return fmt::format("../../{}", resource);
}

class Window final : public tinygl::Window
{
public:
    using tinygl::Window::Window;
    void init() override;
    void processInput() override;
    void draw() override;
private:
    tinygl::ShaderProgram program;
    tinygl::Buffer vbo{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw};
    tinygl::Buffer ibo{tinygl::Buffer::Type::IndexBuffer, tinygl::Buffer::UsagePattern::StaticDraw};
    tinygl::VertexArrayObject vao;
    tinygl::Texture texture0{
        tinygl::Texture::Target::Target2D,
        resourcePath("resources/textures/container.jpg"),
        GL_RGB, GL_RGB, true, 0
    };
    tinygl::Texture texture1{
        tinygl::Texture::Target::Target2D,
        resourcePath("resources/textures/awesomeface.png"),
        GL_RGBA, GL_RGBA, true, 1
    };
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "transformations.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "transformations.frag");
    program.link();

    program.use();
    program.setUniformValue("texture0", 0);
    program.setUniformValue("texture1", 1);

    const GLfloat vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
    };
    vbo.bind();
    vbo.fill(vertices, sizeof(vertices));
    vbo.unbind();

    const GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    ibo.bind();
    ibo.fill(indices, sizeof(indices));
    ibo.unbind();

    vao.bind();

    vbo.bind();
    vao.setAttributeArray(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(0);
    vao.setAttributeArray(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    vao.enableAttributeArray(1);
    vbo.unbind();

    ibo.bind();
    vao.unbind();
}

void Window::processInput()
{
    if (getKey(tinygl::Key::Escape) == tinygl::KeyState::Press) {
        setShouldClose(true);
    }
}

void Window::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    texture0.bind();
    texture1.bind();

    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(0.5f, -0.5f, 1.0f));
    transformation = glm::rotate(transformation, tinygl::getTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    program.use();
    program.setUniformValue("transformation", transformation);
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

MAIN
