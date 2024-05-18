#ifndef PATH_H
#define PATH_H

#include <vector>
#include "Event.h"

class Path {
public:
    Path();
    ~Path();

    void addEvent(const Event& event);
    void triggerEvents();

    void render(SDL_Renderer* renderer);

private:
    std::vector<Event> events;
};

#endif // PATH_H