/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "GameObject.h"

GameObject::GameObject(glm::vec2 pos, Texture2D sprite)
    : Position(pos), Color(glm::vec3(1.0f)), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false), IsMirrored(false)
{
    Size = glm::vec2(sprite.Width, sprite.Height);
}

void GameObject::Draw()
{
    
    Utility::GetRenderer()->DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color, IsMirrored);
}

GameObject::~GameObject()
{
}

void GameObject::SetSize(glm::vec2 size)
{
    Size = size;
}
glm::vec2& GameObject::GetSize()
{
    return Size;
}
void GameObject::SetPosition(glm::vec2 pos)
{
    Position = pos;
}
glm::vec2& GameObject::GetPosition()
{
    return Position;
}

bool GameObject::CheckCollision(GameObject &other)
{
    return Position.x + Size.x >= other.Position.x && Position.x <= other.Position.x + other.Size.x && Position.y + Size.y >= other.Position.y && Position.y <= other.Position.y + other.Size.y;
}
