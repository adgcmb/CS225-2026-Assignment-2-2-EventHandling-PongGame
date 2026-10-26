
#include "player.hh"

#include <AEEngine.h>

Player::Player(int x, int y) : speed(300.0f), direction(0), inputHandler(this, &Player::onInput)
{
    attach(new PositionComponent(x, y));
}

void Player::onInput(InputEvent* event)
{
    switch (event->direction)
    {
        case InputEvent::UP:
            direction = 1;
            break;

        case InputEvent::DOWN:
            direction = -1;
            break;

        case InputEvent::STOP:
            direction = 0;
            break;
    }
}

void Player::Update()
{
    PositionComponent* position = static_cast<PositionComponent*>(getComponent("Position"));

    if (position == nullptr)
    {
        return;
    }

    float deltaTime = (float)AEGetFrameTime();

    int newY = position->getY() + static_cast<int>(direction * speed * deltaTime);

    position->setPosition(position->getX(), newY);
}

void Player::Draw()
{
    PositionComponent* position = static_cast<PositionComponent*>(getComponent("Position"));

    if (position == nullptr)
    {
        return;
    }

    AEGfxRect((float)position->getX(), (float)position->getY(), 0.0f, 20.0f, 100.0f, AEGfxColor(255, 255, 255));
}

EventHandler<Player, InputEvent>* Player::getInputHandler()
{
    return &inputHandler;
}
