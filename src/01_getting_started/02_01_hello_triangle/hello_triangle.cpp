#include "main.h"
#include <tinygl/tinygl.h>
#include <iostream>

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
    tinygl::VertexArrayObject vao;
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "hello_triangle.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "hello_triangle.frag");
    program.link();

    const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };
    vbo.bind();
    vbo.fill(vertices, sizeof(vertices));
    vbo.unbind();

    vao.bind();
    vbo.bind();
    vao.setAttributeArray(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(0);
    vbo.unbind();
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
    program.use();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

MAIN
