#include "main.h"
#include <tinygl/tinygl.h>
#include <iostream>

class window final : public tinygl::window
{
public:
    using tinygl::window::window;
    void process_input() override;
    void draw() override;
};

void window::process_input()
{
    if (get_key(tinygl::keyboard::key::escape) == tinygl::keyboard::key_state::press) {
        set_should_close(true);
    }
}

void window::draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

MAIN
