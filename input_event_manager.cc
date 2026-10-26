#include "input_event_manager.hh"

void InputEventManager::update()
{
    if (AEInputKeyPressed('W'))
    {
        InputEvent event(InputEvent::UP);
        notifyEvent(&event);
    }
    else if (AEInputKeyPressed('S'))
    {
        InputEvent event(InputEvent::DOWN);
        notifyEvent(&event);
    }
    else
    {
        InputEvent event(InputEvent::STOP);
        notifyEvent(&event);
    }
}
