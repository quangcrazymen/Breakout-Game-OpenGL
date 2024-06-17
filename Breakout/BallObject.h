#pragma once
#include "GameObject.h"
class BallObject : public GameObject
{
public:
    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

    glm::vec2 Move(float dt, unsigned int window_width);
    void      Reset(glm::vec2 position, glm::vec2 velocity);

    // ball state	
    float     Radius;
    bool      Stuck;
    bool    Sticky, PassThrough;
};

