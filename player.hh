
#pragma once

#include "src/Framework/entity.hh"
#include "src/Framework/event_handlers.hh"
#include "pong_events.hh"
#include "src/Components/position_component.hh"

class Player : public Entity
{
private:
    float speed;
    int direction;

    EventHandler<Player, InputEvent> inputHandler;

public:
    Player(int x, int y);

    void onInput(InputEvent* event);

    void Update() override;
    void Draw() override;

    EventHandler<Player, InputEvent>* getInputHandler();
};
