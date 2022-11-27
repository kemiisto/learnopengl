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
    std::array<tinygl::ShaderProgram, 2> programs;
    std::array<tinygl::Buffer, 2> vbos {
        tinygl::Buffer{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw},
        tinygl::Buffer{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw}
    };
    std::array<tinygl::VertexArrayObject, 2> vaos;
};

void Window::init()
{
    const std::array<std::string, 2> fragmentShaderFileNames {
        "hello_triangle_exercise3.frag",
        "hello_triangle_exercise3_alt.frag"
    };

    for (int i = 0; i < 2; ++i) {
        programs[i].addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "hello_triangle_exercise3.vert");
        programs[i].addShaderFromSourceFile(tinygl::Shader::Type::Fragment, fragmentShaderFileNames[i]);
        programs[i].link();
    }

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

    for (int i = 0; i < 2; ++i) {
        programs[i].use();
        vaos[i].bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

MAIN
