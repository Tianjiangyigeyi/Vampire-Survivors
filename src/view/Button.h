#include "../viewmodel/Texture.h"
#include "../viewmodel/ResourceManager.h"
#include "../viewmodel/Utility.h"
#include "../viewmodel/Text.h"
#include <string>

class Button
{
public:
    float x,y;
    float width,height;
    bool hovered;
    bool pressed;
    std::string Button_text;

    Texture2D normal_texture;
    Texture2D hovered_texture;
    Texture2D pressed_texture;

    Button(float x,float y,float width,float height,std::string button_text)
        :x(x),y(y),width(width),height(height),hovered(false),pressed(false),Button_text(button_text) {};
    

    void Render();
    void Check_Hover_Press(float cursor_x, float cursor_y, bool button_left);

    void DrawButton(float cursor_x, float cursor_y, bool button_left);


};