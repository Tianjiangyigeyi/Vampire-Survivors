#ifndef GAME_H
#define GAME_H

#include "../common/config.h"
#include "../viewmodel/Utility.h"
#include "../viewmodel/GameObject.h"
#include "PlayerObject.h"

// Represents the current state of the game
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};


const glm::vec2 PLAYER_SIZE(10.0f, 10.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(50.0f);
// Initial velocity of the Ball
// const glm::vec2 INITIAL_BALL_VELOCITY(0.0f, -350.0f);
const glm::vec2 RUNTIME_BALL_VELOCITY(10.0f, -35.f);
// Radius of the ball object


extern PlayerObject *Player;


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

};

#endif