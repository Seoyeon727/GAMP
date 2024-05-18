#ifndef CHISAM_H
#define CHISAM_H

#include "SDL2/SDL.h"
#include "Stats.h"
#include <string>  // 추가: string 헤더 파일 포함

class ChiSam {
public:
    ChiSam();
    ~ChiSam();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void collectItem(const std::string& itemType);  // 수정: std::string 사용

    void render(SDL_Renderer* renderer);

    // Getters for stats
    int getHealth() const;
    int getStress() const;
    int getPopularity() const;
    int getAcademicPerformance() const;

private:
    SDL_Texture* texture;
    SDL_Rect position;
    Stats stats;

    void loadTexture(SDL_Renderer* renderer);
};

#endif // CHISAM_H
