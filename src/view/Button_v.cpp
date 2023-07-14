#include "../common/config.h"
#include "Text.h"
#include "../util/Utility.h"
extern Voice v;
void Button::Render(bool have_texture)
{

    Utility::GetRenderer()->DrawSprite(ResourceManager::GetTexture(Button_text), glm::vec2(x, y), glm::vec2(width, height), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    if(!have_texture)
        text_character::generate_text(Button_text,glm::vec2(x,y),glm::vec2(width,height),1,0.0f,glm::vec3(1.0f, 1.0f, 1.0f),false);
   
}

void Button::Check_Hover_Press(float cursor_x, float cursor_y, bool button_left)
{

    if(cursor_x >= x && cursor_x <= x + width && cursor_y >= y && cursor_y <= y + height)
    {
        // std::cout<<"---In Button---"<<std::endl;
        v.play(1, 0);
    }
    
}

void Button::DrawButton(float cursor_x, float cursor_y, bool &button_left, bool have_texture)
{
    Check_Hover_Press(cursor_x, cursor_y, button_left);
    Render(have_texture);
    button_left = false;
}
