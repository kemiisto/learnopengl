#ifndef LEARNOPENGL_MAIN_H
#define LEARNOPENGL_MAIN_H

#define MAIN                                     \
int main()                                       \
{                                                \
    try {                                        \
        Window window(800, 600, NAME);           \
        window.run();                            \
    } catch (const std::exception& e) {          \
        std::cerr << e.what() << std::endl;      \
        return EXIT_FAILURE;                     \
    }                                            \
                                                 \
    return EXIT_SUCCESS;                         \
}                                                \

#endif //LEARNOPENGL_MAIN_H
