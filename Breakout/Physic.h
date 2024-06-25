#pragma once
#include "GameObject.h"
#include "BallObject.h"
#include "Game.h"
#include "Define.h"
#include "glm/glm.hpp"
#include "PostProcessor.h"
#include "Subject.h"

// Represents the four possible (collision) directions
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};
// Defines a Collision typedef that represents collision data
typedef std::tuple<bool, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>
class Physic : public Subject
{
public:
    Physic(Game *game) {
        this->game = game;
    }
    Game* game;

    void DoCollisions();
    
    bool CheckCollision(GameObject& one, GameObject& two); // AABB - AABB collision

    Collision CheckCollision(BallObject& one, GameObject& two); // AABB - Circle collision

    // calculates which direction a vector is facing (N,E,S or W)
    Direction VectorDirection(glm::vec2 target);
};

