#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject{
public:
    Actor(int imageID, int x_location, int y_location, Direction dir, int depth, double size, StudentWorld* temp):GraphObject(imageID, x_location, y_location, dir, depth, size){
        moveTo(x_location, y_location);
        world = temp;
        x_loc = x_location;
        y_loc = y_location;
    }
    virtual void doSomething();
    StudentWorld* getWorld(){
        return world;
    }
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
    Wall(int x_location, int y_location, StudentWorld* temp):Actor(IID_WALL, x_location, y_location, 0, 0, 1, temp){
        
    }
    virtual bool isAlive(){
        return true;
    }
    //walls do something does nothing
    virtual void doSomething(){
        return;
    }
};
#endif // ACTOR_H_
