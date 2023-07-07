#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../viewmodel/ResourceManager.h"
#include "../viewmodel/SpriteRenderer.h"
#include "GameLevel.h"
#include "GameObject.h"
#include "BallObject.h"
#include "PlayerObject.h"

// Represents the current state of the game
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};
enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};
typedef std::tuple<bool, Direction, glm::vec2> Collision;
// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 100.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);
// Initial velocity of the Ball
// const glm::vec2 INITIAL_BALL_VELOCITY(0.0f, -350.0f);
const glm::vec2 RUNTIME_BALL_VELOCITY(100.0f, -350.f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;

extern SpriteRenderer *Renderer;
extern PlayerObject *Player;
extern BallObject *Ball;

Direction VectorDirection(glm::vec2 target);
Collision CheckCollision(BallObject &one, GameObject &two);
bool CheckCollision(GameObject &one, GameObject &two);

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    // const int nTimes = 5;
    // const glm::vec2 center = glm::vec2(nTimes * Width / 2, nTimes * Height / 2);
    GameState State;
    bool Keys[1024];
    bool Button_left;
    unsigned int Width, Height;
    std::vector<GameLevel> Levels;
    std::vector<BallObject *> Balls;
    unsigned int Level;

    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void DoCollisions(BallObject *thisBall);
    void ResetLevel();
    glm::vec2 InitialVelocity();
};

#endif