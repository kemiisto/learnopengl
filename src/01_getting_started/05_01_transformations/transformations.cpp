#include "main.h"
#include "resource.h"
#include <tinyla/geom.hpp>
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
    tinygl::texture texture0{
        tinygl::texture::target::target_2d,
        resourcePath("textures/container.jpg"),
        GL_RGB, GL_RGB, true, 0
    };
    tinygl::texture texture1{
        tinygl::texture::target::target_2d,
        resourcePath("textures/awesomeface.png"),
        GL_RGBA, GL_RGBA, true, 1
    };
};

void window::init()
{
    program.add_shader_from_source_file(tinygl::shader::type::vertex, "transformations.vert");
    program.add_shader_from_source_file(tinygl::shader::type::fragment, "transformations.frag");
    program.link();

    program.use();
    program.set_uniform_value("texture0", 0);
    program.set_uniform_value("texture1", 1);

    constexpr GLfloat vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
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
    vao.set_attribute_array(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    vao.enable_attribute_array(0);
    vao.set_attribute_array(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    vao.enable_attribute_array(1);
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

    texture0.bind();
    texture1.bind();

    auto transformation = tinyla::mat4f{tinyla::mat_init::identity};
    tinyla::geom::post_translate(transformation, {0.5f, -0.5f, 1.0f});
    tinyla::geom::post_rotate(transformation,
        tinyla::geom::angle<float>::from_radians(tinygl::get_time<float>()), {0.0f, 0.0f, 1.0f});

    program.use();
    program.set_uniform_value("transformation", transformation);
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

MAIN
