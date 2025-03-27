#ifndef LEARNOPENGL_MAIN_H
#define LEARNOPENGL_MAIN_H

#define MAIN                                     \
int main()                                       \
{                                                \
    try {                                        \
        tinygl::init(3, 3);                      \
        window w(800, 600, NAME);                \
        w.run();                                 \
    } catch (const std::exception& e) {          \
        tinygl::terminate();                     \
        std::cerr << e.what() << std::endl;      \
        return EXIT_FAILURE;                     \
    }                                            \
                                                 \
    return EXIT_SUCCESS;                         \
}                                                \

#endif //LEARNOPENGL_MAIN_H
