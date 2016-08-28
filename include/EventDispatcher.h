#ifndef EVENT_DISPATCHER
#define EVENT_DISPATCHER

#include <unordered_map>
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
    CLOSE,
    UNBIND
};

struct SizeData {
    int width;
    int height;
};

union Data {
    bool repeat;
    SizeData size;
};

class EventDispatcher {
public:
    EventDispatcher();

    // No return value, no parameters
    void bind(EventType type, std::function<void (Data)> function);

    //Provides default event struct
    //  Event.repeat = false
    //  Event.size.width = 0;
    //  Event.size.height = 0;
    void dispatch(EventType type);
    //Event union stores extra information, such as window resize values
    void dispatch(EventType type, Data data);

private:
    std::unordered_multimap<EventType, std::function<void(Data)>> m_callbackMap;

};

#endif