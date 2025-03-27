#include "main.h"
#include "resource.h"
#include <tinygl/tinygl.h>
#include <fmt/format.h>
#include <iostream>

class window final : public tinygl::window
{
public:
    using tinygl::window::window;
    void init() override;
    void process_input() override;
    void draw() override;
private:
    tinygl::shader_program program;
    tinygl::buffer vbo{tinygl::buffer::type::vertex_buffer, tinygl::buffer::usage_pattern::static_draw};
    tinygl::buffer ibo{tinygl::buffer::type::index_buffer, tinygl::buffer::usage_pattern::static_draw};
    tinygl::vertex_array_object vao;
    tinygl::texture texture{
        tinygl::texture::target::target_2d,
        resourcePath("textures/container.jpg"),
        GL_RGB, GL_RGB, true, 0
    };
};

void window::init()
{
    program.add_shader_from_source_file(tinygl::shader::type::vertex, "textures.vert");
    program.add_shader_from_source_file(tinygl::shader::type::fragment, "textures.frag");
    program.link();

    constexpr GLfloat vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    vbo.bind();
    vbo.create(sizeof(vertices), vertices);
    vbo.unbind();

    const GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    ibo.bind();
    ibo.create(sizeof(indices), indices);
    ibo.unbind();

    vao.bind();
    vbo.bind();
    vao.set_attribute_array(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    vao.enable_attribute_array(0);
    vao.set_attribute_array(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    vao.enable_attribute_array(1);
    vao.set_attribute_array(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 6 * sizeof(GLfloat));
    vao.enable_attribute_array(2);
    vbo.unbind();
    ibo.bind();
    vao.unbind();
}

void window::process_input()
{
    if (get_key(tinygl::keyboard::key::escape) == tinygl::keyboard::key_state::press) {
        set_should_close(true);
    }
}

void window::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    texture.bind();
    program.use();
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

MAIN
