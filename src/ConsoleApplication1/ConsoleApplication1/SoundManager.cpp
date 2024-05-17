#include "SoundManager.h"

SoundManager::SoundManager() {
    // Initialize SDL_mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

SoundManager::~SoundManager() {
    for (auto& sound : soundMap) {
        Mix_FreeChunk(sound.second);
    }
    Mix_CloseAudio();
}

bool SoundManager::loadSound(const std::string& id, const std::string& filename) {
    Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    if (sound == nullptr) {
        return false;
    }
    soundMap[id] = sound;
    return true;
}

void SoundManager::playSound(const std::string& id) {
    Mix_PlayChannel(-1, soundMap[id], 0);
}
