#include "EventDispatcher.h"

EventDispatcher::EventDispatcher() {

}

void EventDispatcher::bind(EventType type, std::function<void (Data)> function) {
    m_callbackMap.emplace(type, function);
}

void EventDispatcher::dispatch(EventType type) {
    Data data = {};
    dispatch(type, data);
}

void EventDispatcher::dispatch(EventType type, Data data) {
    auto range = m_callbackMap.equal_range(type);

    for(auto it = range.first; it != range.second; ++it){
        it->second(data);
    }
}