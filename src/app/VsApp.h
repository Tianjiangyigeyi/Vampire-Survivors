#ifndef VSAPP_H
#define VSAPP_H

#include "../view/Game.h"
#include "../common/config.h"
#include <windows.h>
#include <iostream>



// 由于OpenGL的C特性，它无法将成员函数作为回调函数
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);


class VsApp
{
public:
    VsApp();
    VsApp(const VsApp &) = delete;
    VsApp &operator=(const VsApp &) = delete;
    ~VsApp() noexcept;

    bool Init();
    int Run();

};
#endif // !VSAPP_H