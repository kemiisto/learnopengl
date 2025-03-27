#include "main.h"
#include <tinygl/tinygl.h>
#include <array>
#include <iostream>

class window final : public tinygl::window
{
public:
    using tinygl::window::window;
    void init() override;
    void process_input() override;
    void draw() override;
private:
    std::array<tinygl::shader_program, 2> programs;
    std::array<tinygl::buffer, 2> vbos {
        tinygl::buffer{tinygl::buffer::type::vertex_buffer, tinygl::buffer::usage_pattern::static_draw},
        tinygl::buffer{tinygl::buffer::type::vertex_buffer, tinygl::buffer::usage_pattern::static_draw}
    };
    std::array<tinygl::vertex_array_object, 2> vaos;
};

void window::init()
{
    const std::array<std::string, 2> fragmentShaderFileNames {
        "hello_triangle_exercise3.frag",
        "hello_triangle_exercise3_alt.frag"
    };

    for (int i = 0; i < 2; ++i) {
        programs[i].add_shader_from_source_file(tinygl::shader::type::vertex, "hello_triangle_exercise3.vert");
        programs[i].add_shader_from_source_file(tinygl::shader::type::fragment, fragmentShaderFileNames[i]);
        programs[i].link();
    }

    constexpr GLfloat vertices[][9] = {
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
        vaos[i].set_attribute_array(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        vaos[i].enable_attribute_array(0);
        vbos[i].unbind();
        vaos[i].unbind();
    }
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

    for (int i = 0; i < 2; ++i) {
        programs[i].use();
        vaos[i].bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

MAIN
