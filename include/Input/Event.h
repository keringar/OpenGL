#ifndef OPENGL_EVENT_H
#define OPENGL_EVENT_H

class Event {
public:
    //Resize event
    struct ResizeEvent {
        unsigned int width;
        unsigned int height;
    };

    //Game events
    enum class GameType {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        ZOOM_IN,
        ZOOM_OUT
    };

    struct GameEvent {
        GameType type;
    };

    //Mouse events
    struct MouseMoveEvent {
        double x;
        double y;
        double scrollOffset;
    };

    //Actual Event Struct
    enum EventType {
        CLOSE,
        TOGGLE_FULLSCREEN,
        RESIZE,
        GAME,
        MOUSE
    };

    EventType type;

    union {
        ResizeEvent size;
        GameEvent game;
        MouseMoveEvent mouse;
    };

    bool repeat;
};

#endif