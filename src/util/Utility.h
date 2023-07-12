#ifndef UTILITY_H
#define UTILITY_H

#include "../precomp.h"
#include "../common/config.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include <string>
#include <memory>
class Utility
{
public:
    static SpriteRenderer *Renderer;
    static void Init(std::shared_ptr<Game> game);
    static void DrawBackground();
    static void DrawBackground(const std::string& background);
    static SpriteRenderer *&GetRenderer();
    static void ResetCamera(glm::vec2 pos, glm::vec2 center, float scale);
    static void DestroyRenderer();
    static void generateBackgroundColorTexture(int x, int y, unsigned int width, unsigned int height, float r, float g, float b);
    static void ClearBckGnd(std::string Bck_gnd);
private:
    Utility();
};

#endif