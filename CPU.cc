#include "cpu.hh"
#include "ball.hh"

#include <AEEngine.h>

// Constructor: initializes the CPU paddle and its collision event handler
CPU::CPU(int x, int y, Ball* ball) : speed(250.0f), followingBall(true), ball(ball), collisionHandler(this, &CPU::onCollision)
{
    // Attach the position component to the CPU entity
    attach(new PositionComponent(x, y));
}

// Handles collision events received from the CollisionEventManager
void CPU::onCollision(CollisionEvent* event)
{
    switch (event->type)
    {
        case CollisionEvent::PLAYER_PADDLE:
            followingBall = true;
            break;

        case CollisionEvent::CPU_PADDLE:
            followingBall = false;
            break;
        case CollisionEvent::TOP_WALL:
        case CollisionEvent::BOTTOM_WALL:
            break;

        case CollisionEvent::LEFT_WALL:
        case CollisionEvent::RIGHT_WALL:
            followingBall = true;
            break;
    }
}

// Updates the CPU paddle position to follow the ball
void CPU::Update()
{
    if (!followingBall || ball == nullptr)
    {
        return;
    }

    PositionComponent* position = static_cast<PositionComponent*>(getComponent("Position"));

    PositionComponent* ballPosition = static_cast<PositionComponent*>(ball->getComponent("Position"));

    if (position == nullptr || ballPosition == nullptr)
    {
        return;
    }

    float deltaTime = (float)AEGetFrameTime();

    float currentY = static_cast<float>(position->getY());
    float targetY = static_cast<float>(ballPosition->getY());

    float movement = speed * deltaTime;

    if (targetY > currentY)
    {
        currentY += movement;

        if (currentY > targetY)
        {
            currentY = targetY;
        }
    }
    else if (targetY < currentY)
    {
        currentY -= movement;

        if (currentY < targetY)
        {
            currentY = targetY;
        }
    }

    position->setPosition(position->getX(), static_cast<int>(currentY));
}

// Draws the CPU paddle on the screen
void CPU::Draw()
{
    PositionComponent* position =
        static_cast<PositionComponent*>(
            getComponent("Position")
            );

    if (position == nullptr)
        return;

    AEGfxRect(
        (float)position->getX(),
        (float)position->getY(),
        0.0f,
        20.0f,
        100.0f,
        AEGfxColor(255, 255, 255)
    );
}

// Returns the CPU collision handler so it can be registered with the CollisionEventManager
EventHandler<CPU, CollisionEvent>* CPU::getCollisionHandler()
{
    return &collisionHandler;
}
