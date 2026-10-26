
#pragma once

#include "src/Framework/event_handlers.hh"
#include <AEEngine.h>

#include "pong_events.hh"

class InputEventManager : public EventManager
{
public:
    void update() override;
};
