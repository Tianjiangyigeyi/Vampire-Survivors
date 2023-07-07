#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../precomp.h"
#include "Utility.h"
#include "Texture.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // object state
    bool IsSolid;
    bool Destroyed;
    bool IsMirrored;
    glm::vec2 Position, Size;
    glm::vec3 Color;
    float Rotation;
    Texture2D Sprite;
    // constructor(s)
    GameObject() = delete; 
    // 如果size不合适直接set
    GameObject(glm::vec2 pos, Texture2D sprite);
    // draw sprite
    virtual void Draw();
    virtual ~GameObject();
    void SetSize(glm::vec2 size);
    glm::vec2& GetSize();
    void SetPosition(glm::vec2 pos);
    glm::vec2& GetPosition();
    bool CheckCollision(GameObject &other);
};



#endif