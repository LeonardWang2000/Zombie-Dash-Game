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
    bool checkPositionFree(int x, int y, Actor* temp);
    bool checkObjectOverlap(int x, int y, Actor* temp, int overlap);
    bool checkPlayerOverlap(int x, int y, int overlap);
    bool checkCitizenOverlap(Actor* temp, int overlap);
    bool isCitizenLeft();
    void setLevelDone();
    int distanceToPlayer(int x, int y);
    int distanceToZombie(int x, int y);
    int getPenelopeX();
    int getPenelopeY();
    bool checkPositionFreePlayer(int x, int y);
//    void setCitizenDead(int x, int y);
private:
    int distanceToActor(int x1, int x2, int y1, int y2);
    Penelope* player;
    void setUpLevel();
    std::vector<Actor*> allActors;
    int score;
    bool levelDone;
};

#endif // STUDENTWORLD_H_
