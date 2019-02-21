#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject{
public:
    Actor(int imageID, int x_location, int y_location, Direction dir, int depth, double size, StudentWorld* temp);
    virtual void doSomething();
    StudentWorld* getWorld();
    virtual bool isAlive() = 0;
private:
    int x_loc;
    int y_loc;
    StudentWorld* world;
};


class Penelope: public Actor{
public:
    Penelope(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
    virtual bool isAlive();
private:
    bool alive;
    int infectionCount;
    int flamethrowerCount;
    bool infectionStatus;
    int numberOfLives;
};


class Wall: public Actor{
public:
    Wall(int x_location, int y_location, StudentWorld* temp);
    virtual bool isAlive();
    //walls do something does nothing
    virtual void doSomething();
};


#endif // ACTOR_H_
