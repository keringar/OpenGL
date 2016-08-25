#ifndef EVENT_DISPATCHER
#define EVENT_DISPATCHER

#include <vector>
#include <map>
#include <functional>

enum class EventType {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    ZOOM_IN,
    ZOOM_OUT,
    TOGGLE_FULLSCREEN,
    RESIZE,
    CLOSE
};

struct Event {
    EventType type;
    bool repeat;
};

class EventDispatcher {
public:
    EventDispatcher();

    // No return value, no parameters
    void bind(Event event, std::function<void (Event)> function);

    void dispatch(Event event);

private:
    std::map<Event, std::vector<std::function<void (Event)>>> m_callbackMap;
};

#endif