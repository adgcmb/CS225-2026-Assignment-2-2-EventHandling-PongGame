#pragma once

#include "pong_events.hh"
#include "src/Framework/entity.hh"
#include "src/Framework/event_handlers.hh"
#include "src/Components/position_component.hh"

class Ball : public Entity
{
private:
    float speedX;
    float speedY;

    float positionX;
    float positionY;

    EventHandler<Ball, CollisionEvent> collisionHandler;

public:
    Ball(int x, int y);

    void Update() override;
    void Draw() override;

    void reverseX();
    void reverseY();

    float getSpeedX() const;
    float getSpeedY() const;

    void reset();

    void onCollision(CollisionEvent* event);

    EventHandler<Ball, CollisionEvent>* getCollisionHandler();
};
