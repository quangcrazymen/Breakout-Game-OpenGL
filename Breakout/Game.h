#pragma once
#include <vector>
#include <irrKlang/irrKlang.h>
#include "SpriteRenderer.h"
#include "GameLevel.h"
#include "PowerUps.h"
enum GameState {
    GAME_ACTIVE,
    GAME_PAUSE,
    GAME_MENU,
    GAME_WIN
};

using namespace irrklang;

extern ISoundEngine* SoundEngine;
class Game
{

public:
    // game state
    GameState    State;
    bool         Keys[1024];
    bool KeysProcessed[1024];
    unsigned int Width, Height;
    // Level
    std::vector<GameLevel> Levels;
    std::vector<PowerUp> PowerUps;
    unsigned int Level;
    unsigned int Lives;

    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    // reset
    void ResetLevel();
    void ResetPlayer();
    // Power-up
    void SpawnPowerUps(GameObject& block);
    void UpdatePowerUps(float dt);
    void ActivatePowerUp(PowerUp& powerUp);

    // GLOBAL RENDERER ?
    class SpriteRenderer* Renderer;
    class GameObject* Player;
    class BallObject* Ball;
    class ParticleGenerator* Particles;
    class PostProcessor* Effects;
    class TextRenderer* Text;
    class Physic* Physics;
    class ScoreBoard* mScoreBoard;
    float ShakeTime = 0.0f;
    // Test Render Random UI on the screen
    class GameObject* testUI;
};


