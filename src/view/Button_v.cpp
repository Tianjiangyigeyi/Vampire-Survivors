#include "../common/config.h"
#include "Text.h"
#include "../util/Utility.h"
void Button::Render(bool have_texture)
{
    if(hovered)
    {
        std::string hovered_text = Button_text + "_hovered";
        //text_character::generate_text(Button_text,glm::vec2(x,y),glm::vec2(width,height),1,0.0f,glm::vec3(1.0f, 1.0f, 1.0f),false);
        //Utility::GetRenderer()->DrawSprite(ResourceManager::GetTexture(hovered_text), glm::vec2(x, y), glm::vec2(width, height), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }
    else
    {
        std::string normal_text = Button_text + "_normal";
        Utility::GetRenderer()->DrawSprite(ResourceManager::GetTexture(Button_text), glm::vec2(x, y), glm::vec2(width, height), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        if(!have_texture)
            text_character::generate_text(Button_text,glm::vec2(x,y),glm::vec2(width,height),1,0.0f,glm::vec3(1.0f, 1.0f, 1.0f),false);
    }
}

void Button::Check_Hover_Press(float cursor_x, float cursor_y, bool button_left)
{

    // std::cout<<"In Check_Hover_Press"<<std::endl;
    // std::cout<<"cursor_x: "<<cursor_x<<"cursor_y: "<<cursor_y<<"button_left: "<<button_left<<std::endl;
    if(cursor_x >= x && cursor_x <= x + width && cursor_y >= y && cursor_y <= y + height)
    {
        hovered = true;
        if(button_left)
        {
            pressed = true;
        }
        else
        {
            pressed = false;
        }
    }
    else
    {
        hovered = false;
        pressed = false;
    }
}

void Button::DrawButton(float cursor_x, float cursor_y, bool &button_left, bool have_texture)
{
    Check_Hover_Press(cursor_x, cursor_y, button_left);
    Render(have_texture);
    button_left = false;
}
