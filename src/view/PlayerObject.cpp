#include "PlayerObject.h"

int count = 0;



PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, unsigned int level, Texture2D sprite)
    : GameObject(pos,  sprite), DamageVelocity(INIT_DAMAGE_VELOCITY * level),  state(0)
{
    for (int i = 0; i < 4; ++i)
    {
        sprites[i] = sprite;
    }
}

// 四个纹理对应四种动作样式，其中第一种是站立不动时的姿势，按照顺序依次传参
PlayerObject::PlayerObject(glm::vec2 pos, Texture2D sprite1, Texture2D sprite2, Texture2D sprite3, Texture2D sprite4)
    : GameObject(pos,  sprite1), DamageVelocity(INIT_DAMAGE_VELOCITY ),  state(0)
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
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::Upgrade()
{
    DamageVelocity = INIT_DAMAGE_VELOCITY;
}

void PlayerObject::Move(glm::vec2 &dir)
{
    count++;
    if (dir != glm::vec2(0.0f, 0.0f))
    {
        Position += dir;
        // 15 代表15帧更换一次动作
        if (count >= 15)
        {
            state = (state + 1) % 4;
            Sprite = sprites[state];
            count = 0;
        }
        IsMirrored = dir.x < 0 ? true : false;
    }
    else
    {
        state = 0;
        Sprite = sprites[state];
    }
}
