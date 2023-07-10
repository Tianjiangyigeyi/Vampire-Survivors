#ifndef UTILITY_H
#define UTILITY_H

#include "../precomp.h"
#include "../common/config.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include <string>

class Utility
{
public:
    static SpriteRenderer *Renderer;
    static void Init();
    static void DrawBackground();
    static void DrawBackground(const std::string& background);
    static SpriteRenderer *&GetRenderer();
    static void ResetCamera(glm::vec2 pos, glm::vec2 center, float scale);

private:
    Utility();
};

#endif