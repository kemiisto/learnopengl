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
    tinygl::vertex_array_object vao;
};

void window::init()
{
    program.add_shader_from_source_file(tinygl::shader::type::vertex, "hello_triangle.vert");
    program.add_shader_from_source_file(tinygl::shader::type::fragment, "hello_triangle.frag");
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
    // Which VBO a vertex attribute takes its data from is determined
    // by the VBO currently bound to GL_ARRAY_BUFFER when calling glVertexAttribPointer().
    // So, first we bound the needed VBO (see above) and then call glVertexAttribPointer().
    vao.set_attribute_array(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    // Since we know that the array is tightly packed (there is no space between the next vertex attribute value)
    // we could've also specified the stride as 0 to let OpenGL determine the stride.
    // vao.set_attribute_array(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    vao.enable_attribute_array(0);
    //
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
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

MAIN
