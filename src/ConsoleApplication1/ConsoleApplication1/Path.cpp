#include "Path.h"

Path::Path() {}

Path::~Path() {}

void Path::addEvent(const Event& event) {
    events.push_back(event);
}

void Path::triggerEvents() {
    for (auto& event : events) {
        event.trigger();
    }
}

void Path::render(SDL_Renderer* renderer) {
    for (auto& event : events) {
        event.render(renderer);
    }
}