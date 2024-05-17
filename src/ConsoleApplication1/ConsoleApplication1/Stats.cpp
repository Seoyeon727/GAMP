#include "Stats.h"

Stats::Stats() : health(100), stress(0), popularity(50), academicPerformance(50) {}

void Stats::increaseHealth(int amount) {
    health += amount;
    if (health > 100) {
        health = 100;
    }
}

void Stats::decreaseHealth(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

int Stats::getHealth() const {
    return health;
}

void Stats::increaseStress(int amount) {
    stress += amount;
    if (stress > 100) {
        stress = 100;
    }
}

void Stats::decreaseStress(int amount) {
    stress -= amount;
    if (stress < 0) {
        stress = 0;
    }
}

int Stats::getStress() const {
    return stress;
}

void Stats::increasePopularity(int amount) {
    popularity += amount;
}

void Stats::decreasePopularity(int amount) {
    popularity -= amount;
}

int Stats::getPopularity() const {
    return popularity;
}

void Stats::increaseAcademicPerformance(int amount) {
    academicPerformance += amount;
}

void Stats::decreaseAcademicPerformance(int amount) {
    academicPerformance -= amount;
}

int Stats::getAcademicPerformance() const {
    return academicPerformance;
}