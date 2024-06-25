#include "Physic.h"

void Physic::DoCollisions()
{
    for (GameObject& box : game->Levels[game->Level].Bricks)
    {
        if (!box.Destroyed)
        {
            Collision collision = CheckCollision(*game->Ball, box);
            if (std::get<0>(collision)) // if collision is true
            {
                // destroy block if not solid
                if (!box.IsSolid) {
                    box.Destroyed = true;
                    notify(*game->Ball, GAIN_SCORE);
                    game->SpawnPowerUps(box);
                    SoundEngine->play2D("audio/bleep.mp3", false);
                }
                else
                {   // if block is solid, enable shake effect
                    game->ShakeTime = 0.05f;
                    game->Effects->Shake = true;
                    SoundEngine->play2D("audio/solid.wav", false);
                }
                // collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (!(game->Ball->PassThrough && !box.IsSolid)) {
                    if (dir == LEFT || dir == RIGHT) // horizontal collision
                    {
                        game->Ball->Velocity.x = -game->Ball->Velocity.x; // reverse horizontal velocity
                        // relocate
                        float penetration = game->Ball->Radius - std::abs(diff_vector.x);
                        if (dir == LEFT)
                            game->Ball->Position.x += penetration; // move ball to right
                        else
                            game->Ball->Position.x -= penetration; // move ball to left;
                    }
                    else // vertical collision
                    {
                        game->Ball->Velocity.y = -game->Ball->Velocity.y; // reverse vertical velocity
                        // relocate
                        float penetration = game->Ball->Radius - std::abs(diff_vector.y);
                        if (dir == UP)
                            game->Ball->Position.y -= penetration; // move ball bback up
                        else
                            game->Ball->Position.y += penetration; // move ball back down
                    }
                }
            }
        }
    }
    for (PowerUp& powerUp : game->PowerUps) {
        if (!powerUp.Destroyed)
        {
            if (powerUp.Position.y >= game->Height)
                powerUp.Destroyed = true;
            if (CheckCollision(*game->Player, powerUp))
            {	// collided with player, now activate powerup
                game->ActivatePowerUp(powerUp);
                powerUp.Destroyed = true;
                powerUp.Activated = true;
                SoundEngine->play2D("audio/powerup.wav", false);
            }
        }
    }
    // check collisions for player pad (unless stuck)
    Collision result = CheckCollision(*game->Ball, *game->Player);
    if (!game->Ball->Stuck && std::get<0>(result))
    {
        // check where it hit the board, and change velocity based on where it hit the board
        float centerBoard = game->Player->Position.x + game->Player->Size.x / 2.0f;
        float distance = (game->Ball->Position.x + game->Ball->Radius) - centerBoard;
        float percentage = distance / (game->Player->Size.x / 2.0f);
        // then move accordingly
        float strength = 2.0f;
        glm::vec2 oldVelocity = game->Ball->Velocity;
        game->Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        //Ball->Velocity.y = -Ball->Velocity.y;
        game->Ball->Velocity = glm::normalize(game->Ball->Velocity) * glm::length(oldVelocity); // keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        // fix sticky paddle
        game->Ball->Velocity.y = -1.0f * abs(game->Ball->Velocity.y);
        game->Ball->Stuck = game->Ball->Sticky;
        SoundEngine->play2D("audio/bleep.wav", false);
    }
}

bool Physic::CheckCollision(GameObject& one, GameObject& two) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}

Collision Physic::CheckCollision(BallObject& one, GameObject& two) // AABB - Circle collision
{
    // get center point circle first 
    glm::vec2 center(one.Position + one.Radius);
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // now that we know the clamped values, add this to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center;

    if (glm::length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

// calculates which direction a vector is facing (N,E,S or W)
Direction Physic::VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}
