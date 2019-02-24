#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"
class StudentWorld;
class Citizen;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject{
public:
    //might not need dir, depth, size
    Actor(int imageID, int x_location, int y_location, Direction dir, int depth, double size, StudentWorld* temp);
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    //most are default alive
    virtual bool isAlive();
    void setDead();
    virtual ~Actor();
    virtual bool isHuman();
    virtual bool isZombie();
    virtual bool canBeMovedOnto();
    virtual void activateIfAppropiate(Actor* a);
    //move to agent
    void incrementTickCount();
    int getTickCount();
private:
    int tickCount;
    bool alive;
    StudentWorld* world;
};


//Make class of immovable objects?

class Wall: public Actor{
public:
    Wall(int x_location, int y_location, StudentWorld* temp);
    //walls do something does nothing
    virtual void doSomething();
    virtual bool canBeMovedOnto();
};
//need to put this under activating object
class ActivatingObject: public Actor{
public:
    ActivatingObject(int imageID, int x_location, int y_location, StudentWorld*temp);
    virtual void doSomething();
};

class Exit: public ActivatingObject{
public:
    Exit(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
    virtual void activateIfAppropiate(Actor* a);
private:
    Citizen* citizen;
};


//Destroying stuff section------------------------------


class Flame: public ActivatingObject{
//    Flame(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
};

class Vomit: public ActivatingObject{
//    Vomit(int x_location, int y_location, Direction dir, StudentWorld* temp);
    virtual void doSomething();
};

class Pit: public ActivatingObject{
//    Pit(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
};

class Landmine:public ActivatingObject{
};

//ALL Agent/DAMAGABLE ITEMS--------------------------------------
class Agent: public Actor{
public:
    Agent(int imageID, int x_location, int y_location, StudentWorld* temp);
    virtual void getDamage();
    virtual bool canBeMovedOnto();
    int appropiateMovementDirection(int change, int direction);
};

//All goodies--------------------------------------------
class Goodie: public ActivatingObject{
//    Goodie(int imageID, int x_location, int y_location, StudentWorld* temp);
//    virtual bool canBeMovedOnto();
};

class VaccineGoodie: public Goodie{
    
};

class GasCanGoodie: public Goodie{
    
};

class LandmineGoodie: public Goodie{
    
};


//HUMANS------------------------------------------------
class Human: public Agent{
public:
    Human(int imageID, int x_location, int y_location, StudentWorld* temp);
    virtual bool isHuman();
    
private:
    int infectionCount;
    bool infectionStatus;
};
//CITIZEN
class Citizen: public Human{
public:
    Citizen(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
private:
};
//PENELOPE
class Penelope: public Human{   
public:
    Penelope(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
    virtual bool isHuman();
private:
    int flamethrowerCount;
    int numberOfLives;
};

//ZOMBIES--------------------
class Zombie: public Agent{
public:
    Zombie(int x_location, int y_location, StudentWorld* temp);
    virtual bool isZombie();
    virtual void doSomething();
private:
    int movementPlan;
};

class SmartZombie: public Zombie{
    SmartZombie(int x_location, int y_location, StudentWorld* temp);
};

class DumbZombie: public Zombie{
public:
    DumbZombie(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
};
#endif // ACTOR_H_
