#pragma once
#include <vector>
#include "GameObject.h"
class GameLevel
{
public:
	// level state
	std::vector<GameObject> Bricks;
	GameLevel(){}
    // loads level from file
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    void Draw(SpriteRenderer& renderer);
    bool IsCompleted();
private:
    void init(std::vector<std::vector<unsigned int>> tileData,
        unsigned int levelWidth, unsigned int levelHeight);
};

