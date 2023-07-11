#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>
#include "../util/Utility.h"
#include "../util/ResourceManager.h"
class text_character
{
public:
    text_character();
    ~text_character();
    static void generate_text(std::string data,glm::vec2 position,glm::vec2 size,int lines, float rotate, glm::vec3 color, bool mirror);
};

#endif