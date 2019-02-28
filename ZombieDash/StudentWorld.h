#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include "Level.h"
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Penelope;
class Actor;
class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    ~StudentWorld();
    bool checkPositionFree(double x, double y, Actor* temp);
    bool checkObjectOverlap(double x, double y, Actor* temp, int overlap) const;
    bool checkPlayerOverlap(double x, double y, int overlap, Actor* temp);
    bool checkCitizenOverlap(Actor* temp, int overlap);
    bool isCitizenLeft();
    void setLevelDone();
    double distanceToPlayer(double x, double y);
    double leastDistanceToZombie(double x, double y);
    int getPenelopeX();
    int getPenelopeY();
    bool checkPositionFreePlayer(double x, double y);
    void addActor(Actor* a);
    void activateOnAppropriateActors(Actor* a);
    bool isZombieVomitTriggerAt(double x, double y) const;
    void closestHuman(double &x, double &y, Actor* temp);
    bool isFlameBlockedAt(double x, double y) const;
//    void setCitizenDead(double x, double y);
private:
    double distanceToActor(double x1, double x2, double y1, double y2);
    Penelope* player;
    void setUpLevel();
    std::vector<Actor*> allActors;
    int score;
    bool levelDone;
};

#endif // STUDENTWORLD_H_
