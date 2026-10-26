#pragma once

#include "src/Framework/event_handlers.hh"
#include "pong_events.hh"
#include "ball.hh"

#include <AEEngine.h>

class Ball;
class Player;
class CPU;

class CollisionEventManager : public EventManager
{
private:
    Ball* ball;
    Player* player;
    CPU* cpu;

public:
    CollisionEventManager(Ball* ball, Player* player, CPU* cpu);

    void update() override;
};
