#include "main.h"
#include <tinygl/tinygl.h>
#include <array>
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
    std::array<tinygl::Buffer, 2> vbos {
        tinygl::Buffer{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw},
        tinygl::Buffer{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw}
    };
    std::array<tinygl::VertexArrayObject, 2> vaos {
        tinygl::VertexArrayObject{},
        tinygl::VertexArrayObject{}
    };
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "hello_triangle_exercise2.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "hello_triangle_exercise2.frag");
    program.link();

    const GLfloat vertices[][9] = {
        {
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
        },
        {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top
        }
    };

    for (int i = 0; i < 2; ++i) {
        vbos[i].bind();
        vbos[i].create(sizeof(vertices[i]), vertices[i]);
        vbos[i].unbind();

        vaos[i].bind();
        vbos[i].bind();
        vaos[i].setAttributeArray(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        vaos[i].enableAttributeArray(0);
        vbos[i].unbind();
        vaos[i].unbind();
    }
}

void Window::processInput()
{
    if (getKey(tinygl::keyboard::Key::Escape) == tinygl::keyboard::KeyState::Press) {
        setShouldClose(true);
    }
}

void Window::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    program.use();
    for (int i = 0; i < 2; ++i) {
        vaos[i].bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

MAIN
