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
    bool checkPositionFree(int x, int y);
    bool checkObjectOverlap(int x, int y, Actor* temp);
private:
    Penelope* player;
    void setUpLevel();
    std::vector<Actor*> allActors;
    int score;
};

#endif // STUDENTWORLD_H_
