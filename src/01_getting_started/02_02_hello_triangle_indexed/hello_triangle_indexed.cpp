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
    tinygl::Buffer ibo{tinygl::Buffer::Type::IndexBuffer, tinygl::Buffer::UsagePattern::StaticDraw};
    tinygl::VertexArrayObject vao;
    bool wireframe = false;
};

void Window::init()
{
    setKeyCallback([this](tinygl::Key key, int scancode, tinygl::KeyAction action, tinygl::Modifier mods) {
        if (key == tinygl::Key::W && action == tinygl::KeyAction::Press) {
            wireframe = !wireframe;
        }
    });

    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "hello_triangle_indexed.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "hello_triangle_indexed.frag");
    program.link();

    const GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    vbo.bind();
    vbo.fill(vertices, sizeof(vertices));
    vbo.unbind();

    GLuint indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };
    ibo.bind();
    ibo.fill(indices, sizeof(indices));
    ibo.unbind();

    vao.bind();
    vbo.bind();
    vao.setAttributeArray(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(0);
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

    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    program.use();
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

MAIN
