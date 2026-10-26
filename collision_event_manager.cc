#include "ball.hh"
#include "CPU.hh"
#include "player.hh"
#include "collision_event_manager.hh"
#include <AEEngine.h>

// Constructor: stores pointers to the ball and both paddles
CollisionEventManager::CollisionEventManager(Ball* ball, Player* player, CPU* cpu) : ball(ball), player(player), cpu(cpu) {}

// Checks collisions between the ball, walls, and paddles
void CollisionEventManager::update()
{
    if (ball == nullptr)
    {
        return;
    }

    PositionComponent* position = static_cast<PositionComponent*>(ball->getComponent("Position"));
    PositionComponent* playerPosition = static_cast<PositionComponent*>(player->getComponent("Position"));
    PositionComponent* cpuPosition = static_cast<PositionComponent*>(cpu->getComponent("Position"));

    if (position == nullptr)
    {
        return;
    }

    float ballY = static_cast<float>(position->getY());
    float halfHeight = static_cast<float>(AEGetSysWindowHeight()) / 2.0f;

    float ballX = static_cast<float>(position->getX());
    float halfWidth = static_cast<float>(AEGetSysWindowWidth()) / 2.0f;

    const float ballRadius = 10.0f;

    // LEFT WALL
    if (ballX - ballRadius <= -halfWidth)
    {
        CollisionEvent event(CollisionEvent::LEFT_WALL);
        notifyEvent(&event);
        return;
    }

    // RIGHT WALL
    if (ballX + ballRadius >= halfWidth)
    {
        CollisionEvent event(CollisionEvent::RIGHT_WALL);
        notifyEvent(&event);
        return;
    }

    // TOP WALL
    if (ballY + ballRadius >= halfHeight && ball->getSpeedY() > 0.0f)
    {
        CollisionEvent event(CollisionEvent::TOP_WALL);
        notifyEvent(&event);
    }
    // BOTTOM WALL
    else if (ballY - ballRadius <= -halfHeight && ball->getSpeedY() < 0.0f)
    {
        CollisionEvent event(CollisionEvent::BOTTOM_WALL);
        notifyEvent(&event);
    }

    // BALL CENTER
    AEVec2 ballCenter = {static_cast<float>(position->getX()), static_cast<float>(position->getY())};

    // PLAYER CENTER
    AEVec2 playerCenter = {static_cast<float>(playerPosition->getX()), static_cast<float>(playerPosition->getY())};

    // CPU CENTER
    AEVec2 cpuCenter = {static_cast<float>(cpuPosition->getX()), static_cast<float>(cpuPosition->getY())};

    // PLAYER COLLISION
    if (ball->getSpeedX() < 0.0f && AEStaticRectToStaticCircle(&playerCenter, 20.0f, 100.0f, &ballCenter, ballRadius))
    {
        CollisionEvent event(CollisionEvent::PLAYER_PADDLE);
        notifyEvent(&event);
    }

    // CPU COLLISION
    if (ball->getSpeedX() > 0.0f && AEStaticRectToStaticCircle(&cpuCenter, 20.0f, 100.0f, &ballCenter, ballRadius))
    {
        CollisionEvent event(CollisionEvent::CPU_PADDLE);
        notifyEvent(&event);
    }
}