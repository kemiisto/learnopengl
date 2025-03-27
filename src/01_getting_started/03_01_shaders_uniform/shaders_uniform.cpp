#include "main.h"
#include <tinygl/tinygl.h>
#include <iostream>
#include <cmath>

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
};

void window::init()
{
    program.add_shader_from_source_file(tinygl::shader::type::vertex, "shaders_uniform.vert");
    program.add_shader_from_source_file(tinygl::shader::type::fragment, "shaders_uniform.frag");
    program.link();

    constexpr GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };
    vbo.bind();
    vbo.create(sizeof(vertices), vertices);
    vbo.unbind();

    vao.bind();
    vbo.bind();
    vao.set_attribute_array(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enable_attribute_array(0);
    vbo.unbind();
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

    program.use();

    auto time = tinygl::get_time<float>();
    auto green = std::sin(time) / 2.0f + 0.5f;
    auto colorLocation = program.uniform_location("color");
    program.set_uniform_value(colorLocation, 0.0f, green, 0.0f, 1.0f);

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

MAIN
