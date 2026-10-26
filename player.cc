
#include "player.hh"
#include <AEEngine.h>

// Constructor: initializes the player's movement speed, direction, and input event handler
Player::Player(int x, int y) : speed(300.0f), direction(0), inputHandler(this, &Player::onInput)
{
    attach(new PositionComponent(x, y));
}

// Handles keyboard input events received from the InputEventManager
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

// Updates the player's position based on the current direction
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

// Draws the player paddle on the screen
void Player::Draw()
{
    PositionComponent* position = static_cast<PositionComponent*>(getComponent("Position"));

    if (position == nullptr)
    {
        return;
    }

    AEGfxRect((float)position->getX(), (float)position->getY(), 0.0f, 20.0f, 100.0f, AEGfxColor(255, 255, 255));
}

// Returns the input event handler so it can be registered with the InputEventManager
EventHandler<Player, InputEvent>* Player::getInputHandler()
{
    return &inputHandler;
}
