#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject{
public:
    //might not need dir, depth, size
    Actor(int imageID, int x_location, int y_location, Direction dir, int depth, double size, StudentWorld* temp);
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    //most are default alive
    virtual bool isAlive();
    virtual ~Actor();
private:
    bool alive;
    StudentWorld* world;
};


class Penelope: public Actor{
public:
    Penelope(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
private:
    int infectionCount;
    int flamethrowerCount;
    bool infectionStatus;
    int numberOfLives;
};
//Make class of immovable objects?

class Wall: public Actor{
public:
    Wall(int x_location, int y_location, StudentWorld* temp);
    //walls do something does nothing
    virtual void doSomething();
};

class Exit: public Actor{
public:
    Exit(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
};

class Pit: public Actor{
    Pit(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
};

class Flame: public Actor{
    Flame(int x_location, int y_location,  Direction dir, StudentWorld* temp);
    virtual void doSomething();
};

#endif // ACTOR_H_
