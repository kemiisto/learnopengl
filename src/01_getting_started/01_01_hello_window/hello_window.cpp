#include "main.h"
#include <tinygl/tinygl.h>
#include <iostream>

class window final : public tinygl::window
{
public:
    using tinygl::window::window;
    void process_input() override;
};

void window::process_input()
{
    if (get_key(tinygl::keyboard::key::escape) == tinygl::keyboard::key_state::press) {
        set_should_close(true);
    }
}

MAIN
