#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int x_location, int y_location, Direction dir, int depth, double size, StudentWorld* temp):GraphObject(imageID, x_location, y_location, dir, depth, size){
    moveTo(x_location, y_location);
    world = temp;
    alive = true;
}
void Actor::doSomething(){
    return;
}

bool Actor::isAlive(){
    return alive;
}

StudentWorld* Actor::getWorld(){
        return world;
}

Actor::~Actor(){
}

void Penelope::doSomething(){
        int ch;
        if (getWorld()->getKey(ch))
        {
            // user hit a key during this tick!
            switch (ch)
            {
                case KEY_PRESS_LEFT:
                    setDirection(left);
                    if(getWorld()->checkPositionFree(getX()-4, getY())){
                        moveTo(getX()-4, getY());
                    }
                    break;
                case KEY_PRESS_RIGHT:
                    setDirection(right);
                    if(getWorld()->checkPositionFree(getX()+4, getY()))
                        moveTo(getX()+4, getY());
                    break;
                case KEY_PRESS_UP:
                    setDirection(up);
                    if(getWorld()->checkPositionFree(getX(), getY()+4))
                        moveTo(getX(), getY()+4);
                    break;
                case KEY_PRESS_DOWN:
                    setDirection(down);
                    if(getWorld()->checkPositionFree(getX(), getY()-4))
                        moveTo(getX(), getY()-4);
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

Penelope::Penelope(int x_location, int y_location, StudentWorld* temp):Actor(IID_PLAYER, x_location, y_location, 0, 0, 1, temp){
    infectionCount = 0;
    numberOfLives = 3;
}





Wall::Wall(int x_location, int y_location, StudentWorld* temp):Actor(IID_WALL, x_location, y_location, 0, 0, 1, temp){}


void Wall::doSomething(){
    return;
}
void Exit::doSomething(){
    
}
void Flame::doSomething(){
    
}
void Pit::doSomething(){
    
}



Exit::Exit(int x_location, int y_location, StudentWorld* temp):Actor(IID_EXIT, x_location, y_location, 0, 0, 1, temp){}


Pit::Pit(int x_location, int y_location, StudentWorld* temp):Actor(IID_PIT, x_location, y_location, 0, 0, 1, temp){}

Flame:: Flame(int x_location, int y_location, Direction dir, StudentWorld* temp):Actor(IID_FLAME, x_location, y_location, dir, 0, 1, temp){}
