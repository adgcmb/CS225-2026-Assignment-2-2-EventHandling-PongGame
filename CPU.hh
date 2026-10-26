#pragma once

#include "src/Framework/entity.hh"
#include "src/Framework/event_handlers.hh"
#include "src/Components/position_component.hh"

#include "pong_events.hh"

class Ball;

class CPU : public Entity
{
private:
    float speed;
    bool followingBall;

    Ball* ball;

    EventHandler<CPU, CollisionEvent> collisionHandler;

public:
    CPU(int x, int y, Ball* ball);

    void Update() override;
    void Draw() override;

    void onCollision(CollisionEvent* event);

    EventHandler<CPU, CollisionEvent>* getCollisionHandler();
};
