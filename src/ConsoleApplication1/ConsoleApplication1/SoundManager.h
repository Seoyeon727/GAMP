#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SDL2/SDL_mixer.h"
#include <string>
#include <map>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    bool loadSound(const std::string& id, const std::string& filename);
    void playSound(const std::string& id);

private:
    std::map<std::string, Mix_Chunk*> soundMap;
};

#endif // SOUNDMANAGER_H
