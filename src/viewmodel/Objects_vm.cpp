#include "../common/config.h"
#include "../util/Utility.h"

EnemyObject::EnemyObject(glm::vec2 pos,  std::string sprite)
        : GameObject(pos,  sprite)
{
}


// resets the ball to initial Stuck Position (if ball is outside window bounds)
void EnemyObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
}

bool EnemyObject::health_adjust(float health_damage){
    health -= health_damage;
    //current_health += recovery;
    if(health <= 0){
        return false;
    }
    return true;
}

EnemyObject::~EnemyObject()
{
}

void EnemyObject::Move(glm::vec2 &dir)
{
    Position += dir;
    IsMirrored = dir.x < 0 ? true : false;
}

GameObject::GameObject(glm::vec2 pos, std::string sprite)
    : Position(pos), Color(glm::vec3(1.0f)), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false), IsMirrored(false)
{
    
    Size = glm::vec2(ResourceManager::GetTexture(sprite).Width, ResourceManager::GetTexture(sprite).Height);
}

void GameObject::Draw()
{
    
    Utility::GetRenderer()->DrawSprite(ResourceManager::GetTexture(Sprite), this->Position, this->Size, this->Rotation, this->Color, IsMirrored);
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

int Pcount = 0;

// 四个纹理对应四种动作样式，其中第一种是站立不动时的姿势，按照顺序依次传参
PlayerObject::PlayerObject(glm::vec2 pos, std::string sprite1, std::string sprite2, std::string sprite3, std::string sprite4)
    : GameObject(pos,  sprite1),  state(0)
{
    sprites[0] = sprite1;
    sprites[1] = sprite2;
    sprites[2] = sprite3;
    sprites[3] = sprite4;
}

void PlayerObject::InitWeapon(std::string Weapon_tra0, std::string Weapon_tra1){
    glm::vec2 W_position = glm::vec2(this->Position.x , this->Position.y );
    the_weapon = new WeaponObject(W_position , Weapon_tra0, Weapon_tra1);
}

// resets the ball to initial Stuck Position (if ball is outside window bounds)
void PlayerObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::Upgrade()
{
    
}

void PlayerObject::Move(glm::vec2 &dir)
{
    Pcount++;
    if (dir != glm::vec2(0.0f, 0.0f))
    {
        Position += dir;
        // 15 代表15帧更换一次动作
        if (Pcount >= 90)
        {
            state = (state + 1) % 4;
            Sprite = sprites[state];
            Pcount = 0;
        }
        if (dir.x != 0)
            IsMirrored = dir.x < 0 ? true : false;
    }
    else
    {
        state = 0;
        Sprite = sprites[state];
    }
}

bool PlayerObject::health_adjust(float health_damage){
    current_health -= health_damage;
    //current_health += recovery;
    if(current_health <= 0){
        return false;
    }
    std::cout << current_health << std::endl;
    return true;
}


int Wcount = 0;

// WeaponObject::WeaponObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
//         : GameObject(pos,  sprite)
// {
// }

WeaponObject::WeaponObject(glm::vec2 pos, std::string sprite0, std::string sprite1)
        : GameObject(pos,  sprite0), state(0)
{
    sprites[0] = sprite0;
    sprites[1] = sprite1;
    SetSize(glm::vec2(ResourceManager::GetTexture(sprite0).Width*1.8, ResourceManager::GetTexture(sprite0).Height*1.8));
    IsMirrored = true;
}


// resets the ball to initial Stuck Position (if ball is outside window bounds)
void WeaponObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
}

WeaponObject::~WeaponObject()
{
}

void WeaponObject::Move(glm::vec2 &dir)
{
    Wcount++;
    Position += dir;
    if (Wcount >= 200)
    {
        Wcount = 0;
        state = (state + 1) % 2;
        Sprite = sprites[state];
        if(!state){
            Position.x += ResourceManager::GetTexture(this->Sprite).Width*1.4;
        }
        else{
            Position.x -= ResourceManager::GetTexture(this->Sprite).Width*1.4;
        }

    }
}