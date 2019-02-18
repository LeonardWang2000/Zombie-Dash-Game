#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject{
public:
    Actor(int imageID, int x_location, int y_location, Direction dir, int depth, double size):GraphObject(imageID, x_location, y_location, dir, depth, size){
        moveTo(x_location, y_location);
    }
    virtual void doSomething();
    
};

class Penelope: public Actor{
public:
    Penelope(int x_location, int y_location):Actor(IID_PLAYER, x_location, y_location, 0, 0, 1){
        isAlive = true;
        infectionCount = 0;
        numberOfLives = 3;
    }
    void doSomething(){
        int ch;
        if (getWorld()->getKey(ch))
        {
            // user hit a key during this tick!
            switch (ch)
            {
                case KEY_PRESS_LEFT:
                    
                    break;
                case KEY_PRESS_RIGHT:
                    break;
                case KEY_PRESS_UP:
                    break;
                case KEY_PRESS_DOWN:
                    break;
                case KEY_PRESS_TAB:
                    break;
                case KEY_PRESS_ENTER:
                    break;
                case KEY_PRESS_SPACE:
                    break;
                    // etc…
            }
        }
    }
private:
    bool isAlive;
    int infectionCount;
    int flamethrowerCount;
    bool infectionStatus;
    int numberOfLives;
};

class Wall: public Actor{
public:
    Wall(int x_location, int y_location):Actor(IID_WALL, x_location, y_location, 0, 0, 1){
        
    }
    //walls do something does nothing
    virtual void doSomething(){
        return;
    }
};
#endif // ACTOR_H_
