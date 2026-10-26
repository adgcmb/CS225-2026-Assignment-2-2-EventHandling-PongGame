#include "ball.hh"
#include <AEEngine.h>


// Constructor: initializes the ball's speed, position, and collision handler
Ball::Ball(int x, int y) : speedX(250.0f), speedY(150.0f), positionX(static_cast<float>(x)), positionY(static_cast<float>(y)), collisionHandler(this, &Ball::onCollision)
{
    attach(new PositionComponent(x, y));
}

// Updates the ball's position every frame
void Ball::Update()
{
    PositionComponent* position = static_cast<PositionComponent*>(getComponent("Position"));

    if (position == nullptr)
    {
        return;
    }

    float deltaTime = (float)AEGetFrameTime();

    positionX += speedX * deltaTime;
    positionY += speedY * deltaTime;

    position->setPosition(static_cast<int>(positionX), static_cast<int>(positionY));
}

// Draws the ball on the screen
void Ball::Draw()
{
    PositionComponent* position = static_cast<PositionComponent*>(getComponent("Position"));

    if (position == nullptr)
    {
        return;
    }

    AEGfxCircle((float)position->getX(), (float)position->getY(), 10.0f, AEGfxColor(255, 255, 255), 20);
}

// Reverses the horizontal direction of the ball
void Ball::reverseX()
{
    speedX = -speedX;
}

// Reverses the vertical direction of the ball
void Ball::reverseY()
{
    speedY = -speedY;
}

// Resets the ball to the center of the screen
void Ball::reset()
{
    positionX = 0.0f;
    positionY = 0.0f;

    speedX = 250.0f;
    speedY = 150.0f;

    PositionComponent* position = static_cast<PositionComponent*>(getComponent("Position"));

    if (position != nullptr)
    {
        position->setPosition(0, 0);
    }
}

//Some getters
float Ball::getSpeedX() const
{
    return speedX;
}

float Ball::getSpeedY() const
{
    return speedY;
}

// Handles collision events received from the CollisionEventManager
void Ball::onCollision(CollisionEvent* event)
{
    switch (event->type)
    {
        case CollisionEvent::PLAYER_PADDLE:
        case CollisionEvent::CPU_PADDLE:
            reverseX();
            break;

        case CollisionEvent::TOP_WALL:
        case CollisionEvent::BOTTOM_WALL:
            reverseY();
            break;

        case CollisionEvent::LEFT_WALL:
        case CollisionEvent::RIGHT_WALL:
            reset();
            break;
    }
}

// Returns the collision event handler for registration with the CollisionEventManager
EventHandler<Ball, CollisionEvent>* Ball::getCollisionHandler()
{
    return &collisionHandler;
}
