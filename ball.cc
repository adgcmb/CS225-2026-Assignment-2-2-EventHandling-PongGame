#include "ball.hh"
#include <AEEngine.h>

Ball::Ball(int x, int y) : speedX(250.0f), speedY(150.0f), positionX(static_cast<float>(x)), positionY(static_cast<float>(y)), collisionHandler(this, &Ball::onCollision)
{
    attach(new PositionComponent(x, y));
}

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

void Ball::Draw()
{
    PositionComponent* position = static_cast<PositionComponent*>(getComponent("Position"));

    if (position == nullptr)
    {
        return;
    }

    AEGfxCircle((float)position->getX(), (float)position->getY(), 10.0f, AEGfxColor(255, 255, 255), 20);
}

void Ball::reverseX()
{
    speedX = -speedX;
}

void Ball::reverseY()
{
    speedY = -speedY;
}

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

float Ball::getSpeedX() const
{
    return speedX;
}

float Ball::getSpeedY() const
{
    return speedY;
}

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

EventHandler<Ball, CollisionEvent>* Ball::getCollisionHandler()
{
    return &collisionHandler;
}
