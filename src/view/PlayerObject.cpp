#include "PlayerObject.h"
bool mirror = false;

int count = 0;

PlayerObject::PlayerObject()
    : GameObject(), DamageVelocity(INIT_DAMAGE_VELOCITY), lv(1), state(0) {}

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, unsigned int level, Texture2D sprite)
    : GameObject(pos, size, sprite), DamageVelocity(INIT_DAMAGE_VELOCITY * level), lv(level), state(0)
{
    for (int i = 0; i < 4; ++i)
    {
        sprites[i] = sprite;
    }
}
PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, unsigned int level, Texture2D sprite1, Texture2D sprite2, Texture2D sprite3, Texture2D sprite4)
    : GameObject(pos, size, sprite1), DamageVelocity(INIT_DAMAGE_VELOCITY * level), lv(level), state(0)
{
    sprites[0] = sprite1;
    sprites[1] = sprite2;
    sprites[2] = sprite3;
    sprites[3] = sprite4;
}

// resets the ball to initial Stuck Position (if ball is outside window bounds)
void PlayerObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->DamageVelocity = INIT_DAMAGE_VELOCITY;
    this->lv = 1;
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::Upgrade()
{
    ++lv;
    DamageVelocity = INIT_DAMAGE_VELOCITY * lv;
}

void PlayerObject::Move(glm::vec2 &dir)
{
    count++;
    if (dir != glm::vec2(0.0f, 0.0f))
    {
        Position += dir;
        if (count >= 15)
        {
            state = (state + 1) % 4;
            Sprite = sprites[state];
            count = 0;
        }
        mirror = dir.x < 0 ? true : false;
    }
    else
    {
        state = 0;
        Sprite = sprites[state];
    }
}

void PlayerObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color, mirror);
}