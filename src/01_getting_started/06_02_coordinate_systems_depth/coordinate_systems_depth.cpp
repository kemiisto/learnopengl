#include "main.h"
#include "resource.h"
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
    tinygl::Texture texture0{
        tinygl::Texture::Target::Target2D,
        resourcePath("textures/container.jpg"),
        GL_RGB, GL_RGB, true, 0
    };
    tinygl::Texture texture1{
        tinygl::Texture::Target::Target2D,
        resourcePath("textures/awesomeface.png"),
        GL_RGBA, GL_RGBA, true, 1
    };
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "coordinate_systems_depth.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "coordinate_systems_depth.frag");
    program.link();

    program.use();
    program.setUniformValue("texture0", 0);
    program.setUniformValue("texture1", 1);

    const GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    vbo.bind();
    vbo.create(sizeof(vertices), vertices);
    vbo.unbind();

    vao.bind();

    vbo.bind();
    vao.setAttributeArray(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(0);
    vao.setAttributeArray(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    vao.enableAttributeArray(1);
    vbo.unbind();

    vao.unbind();

    glEnable(GL_DEPTH_TEST);
}

void Window::processInput()
{
    if (getKey(tinygl::keyboard::Key::Escape) == tinygl::keyboard::KeyState::Press) {
        setShouldClose(true);
    }
}

void Window::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture0.bind();
    texture1.bind();

    auto model = tinygl::Mat4{};
    model.postRotate(tinygl::radiansToDegrees(tinygl::getTime<float>()), {0.5f, 1.0f, 0.0f});

    auto view = tinygl::Mat4{};
    view.postTranslate({0.0f, 0.0f, -3.0f});


    auto projection = tinygl::Mat4::perspective(45.0f, 800.0f/600.0f, 0.1f, 100.0f);

    program.use();
    program.setUniformValue("model", model);
    program.setUniformValue("view", view);
    program.setUniformValue("projection", projection);

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

MAIN

