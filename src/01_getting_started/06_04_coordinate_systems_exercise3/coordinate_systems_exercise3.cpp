#include "main.h"
#include "resource.h"
#include <tinyla/geom.hpp>
#include <tinygl/tinygl.h>
#include <iostream>

using namespace tinyla::geom::literals;

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
    program.add_shader_from_source_file(tinygl::shader::type::vertex, "coordinate_systems_exercise3.vert");
    program.add_shader_from_source_file(tinygl::shader::type::fragment, "coordinate_systems_exercise3.frag");
    program.link();

    program.use();
    program.set_uniform_value("texture0", 0);
    program.set_uniform_value("texture1", 1);

    constexpr GLfloat vertices[] = {
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
    vao.set_attribute_array(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    vao.enable_attribute_array(0);
    vao.set_attribute_array(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));
    vao.enable_attribute_array(1);
    vbo.unbind();

    vao.unbind();

    glEnable(GL_DEPTH_TEST);
}

void window::process_input()
{
    if (get_key(tinygl::keyboard::key::escape) == tinygl::keyboard::key_state::press) {
        set_should_close(true);
    }
}

void window::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture0.bind();
    texture1.bind();

    const tinyla::vec3f cubePositions[] = {
        {0.0f, 0.0f, 0.0f},
        {2.0f, 5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        {2.4f, -0.4f, -3.5f},
        {-1.7f, 3.0f, -7.5f},
        {1.3f, -2.0f, -2.5f},
        {1.5f, 2.0f, -2.5f},
        {1.5f, 0.2f, -1.5f},
        {-1.3f, 1.0f, -1.5f}
    };

    program.use();
    vao.bind();

    auto view = tinyla::mat4f{tinyla::mat_init::identity};
    tinyla::geom::post_translate(view, {0.0f, 0.0f, -3.0f});
    program.set_uniform_value("view", view);

    constexpr auto frustum = tinyla::geom::frustum{45.0_degf, 800.0f/600.0f, 0.1f, 100.0f};
    auto projection = tinyla::geom::perspective(frustum,
        tinyla::geom::handedness::right, tinyla::geom::clip_volume::minus_one_to_one);
    program.set_uniform_value("projection", projection);

    for (int i = 0; i < 10; ++i) {
        auto model = tinyla::mat4f{tinyla::mat_init::identity};
        tinyla::geom::post_translate(model, cubePositions[i]);
        if (i % 3 == 0) {
            tinyla::geom::post_rotate(model,
                tinyla::geom::angle<float>::from_degrees(tinygl::get_time<float>() * 50.0f), {1.0f, 0.3f, 0.5f});
        } else {
            tinyla::geom::post_rotate(model,
                tinyla::geom::angle<float>::from_degrees(20.0f * i), {1.0f, 0.3f, 0.5f});
        }

        program.set_uniform_value("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}

MAIN

