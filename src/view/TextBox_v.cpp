#include "../common/config.h"
#include "../util/Utility.h"
#include "Text.h"

void TextBox::Render()
{
    if(bckgrnd)
    {
        glClearColor(bckgrnd_color.x, bckgrnd_color.y, bckgrnd_color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else
    {
        bckgrnd_texture = ResourceManager::GetTexture(texture_text);
        Utility::GetRenderer()->DrawSprite(bckgrnd_texture, glm::vec2(x, y), glm::vec2(width, height), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    }
    text_character::generate_text(text, glm::vec2(x, y), glm::vec2(width, height), 1, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), false);
}

void TextBox::setText(std::string new_text)
{
    text = new_text;
}