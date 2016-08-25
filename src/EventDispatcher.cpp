#include "Events/EventDispatcher.h"

EventDispatcher::EventDispatcher() {

}

void EventDispatcher::bind(Event event, std::function<void(Event)> function) {
    auto iterator = m_callbackMap.find(event);
    if(iterator != m_callbackMap.end()){
        iterator->second.push_back(function);
    }
}

void EventDispatcher::dispatch(Event event) {
    auto iterator = m_callbackMap.find(evet);
    if(iterator != m_callbackMap.end()){
        for(const auto& function : iterator->second){
            function(event);
        }
    }
}