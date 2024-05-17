#ifndef STATS_H
#define STATS_H

class Stats {
public:
    Stats();

    void increaseHealth(int amount);
    void decreaseHealth(int amount);
    int getHealth() const;

    void increaseStress(int amount);
    void decreaseStress(int amount);
    int getStress() const;

    void increasePopularity(int amount);
    void decreasePopularity(int amount);
    int getPopularity() const;

    void increaseAcademicPerformance(int amount);
    void decreaseAcademicPerformance(int amount);
    int getAcademicPerformance() const;

private:
    int health;
    int stress;
    int popularity;
    int academicPerformance;
};

#endif // STATS_H