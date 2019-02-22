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
    void setDead();
    virtual ~Actor();
    virtual bool isHuman();
    virtual bool canBeMovedOnto();
private:
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

class Exit: public Actor{
public:
    Exit(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
};


//Destroying stuff section------------------------------
class DestroyStuff: public Actor{
    
};
    //Projectiles Section---------------------------------------
class Projectiles: public DestroyStuff{
    
};

class Flame: public Projectiles{
//    Flame(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
};

class Vomit: public Projectiles{
//    Vomit(int x_location, int y_location, Direction dir, StudentWorld* temp);
    virtual void doSomething();
};

class Pit: public DestroyStuff{
//    Pit(int x_location, int y_location, StudentWorld* temp);
    virtual void doSomething();
};

class Landmine:public DestroyStuff{
    //LANDMINE in both destroy and damagable
};

//ALL DESTROYABLE/DAMAGABLE ITEMS--------------------------------------
class Destroyable: public Actor{
public:
    Destroyable(int imageID, int x_location, int y_location, StudentWorld* temp);
    virtual void getDamage();
    virtual bool canBeMovedOnto();
};

//All goodies--------------------------------------------
class Goodie: public Destroyable{
    Goodie(int imageID, int x_location, int y_location, StudentWorld* temp);
    virtual bool canBeMovedOnto();
};

class VaccineGoodie: public Goodie{
    
};

class GasCanGoodie: public Goodie{
    
};

class LandmineGoodie: public Goodie{
    
};


//HUMANS------------------------------------------------
class Human: public Destroyable{
public:
    Human(int imageID, int x_location, int y_location, StudentWorld* temp);
    virtual bool isHuman();
private:
    int infectionCount;
    bool infectionStatus;
};

class Citizen: public Human{
public:
    Citizen(int imageID, int x_location, int y_location, StudentWorld* temp);
};

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
class Zombie: public Destroyable{
public:
    Zombie(int x_location, int y_location, StudentWorld* temp);
};

class SmartZombie: public Zombie{
    SmartZombie(int x_location, int y_location, StudentWorld* temp);
};

class DumbZombie: public Zombie{
    DumbZombie(int x_location, int y_location, StudentWorld* temp);
};
#endif // ACTOR_H_
