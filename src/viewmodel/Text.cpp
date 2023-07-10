#include "Text.h"


text_character::text_character(){}
text_character::~text_character() {}

void text_character::generate_text(std::string data,glm::vec2 position,glm::vec2 size,int lines, float rotate, glm::vec3 color, bool mirror)
{
    //一行当中的字符数目
    int blocks_one_line=data.size()/lines;
    //以下为单个字符占据的宽与高
    float width=size.x/blocks_one_line;
    float height=size.y/lines;
    glm::vec2 temp_size;
    temp_size.x=width;
    temp_size.y=height;
    for(int i=0;i<lines;i++)
    {
        for(int j=0;j<blocks_one_line;j++)
        {
            std::string temp=data.substr(i*blocks_one_line+j,1);
            if(temp[0]==' ') temp="space";
            glm::vec2 temp_position;
            temp_position.x=position.x+width*j;
            temp_position.y=position.y-height*i;
            Utility::GetRenderer()->DrawSprite(ResourceManager::GetTexture(temp),temp_position,temp_size,rotate,color,mirror);
        }
    }
}