#ifndef VSAPP_H
#define VSAPP_H

#include "../common/config.h"
#include "../util/Utility.h"
#include "../viewmodel/GameViewModel.h"
#include "../view/GameView.h"
#include <windows.h>
#include <iostream>
#include <memory>
#include "functional"

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
    void Attach(std::function<void(bool*)> observer) {
        observers.push_back(observer);
    }
    void Notify(bool *Keys, float dt) {
        for (auto& observer : observers) {
            observer(Keys);
        }
    }

private:
    std::shared_ptr<GameViewModel> p_viewmodel;
    std::shared_ptr<GameView> p_view;
    std::vector<std::function<void(bool*)>> observers;
};
#endif // !VSAPP_H