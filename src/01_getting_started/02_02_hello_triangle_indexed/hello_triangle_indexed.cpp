#include "main.h"
#include <tinygl/tinygl.h>
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
    bool wireframe = false;
};

void window::init()
{
    set_key_callback([this](
            tinygl::keyboard::key key,
            [[maybe_unused]] int scancode,
            tinygl::input::action action,
            [[maybe_unused]] tinygl::input::modifier mods) {
        if (key == tinygl::keyboard::key::w && action == tinygl::input::action::press) {
            wireframe = !wireframe;
        }
    });

    program.add_shader_from_source_file(tinygl::shader::type::vertex, "hello_triangle_indexed.vert");
    program.add_shader_from_source_file(tinygl::shader::type::fragment, "hello_triangle_indexed.frag");
    program.link();

    constexpr GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    vbo.bind();
    vbo.create(sizeof(vertices), vertices);
    vbo.unbind();

    GLuint indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };
    ibo.bind();
    ibo.create(sizeof(indices), indices);
    ibo.unbind();

    vao.bind();
    vbo.bind();
    vao.set_attribute_array(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enable_attribute_array(0);
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
