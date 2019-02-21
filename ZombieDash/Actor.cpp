#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int x_location, int y_location, Direction dir, int depth, double size, StudentWorld* temp):GraphObject(imageID, x_location, y_location, dir, depth, size){
    moveTo(x_location, y_location);
    world = temp;
    x_loc = x_location;
    y_loc = y_location;
}
void Actor::doSomething(){
    
}


StudentWorld* Actor::getWorld(){
        return world;
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
    alive = true;
    infectionCount = 0;
    numberOfLives = 3;
}

bool Penelope::isAlive(){
    return alive;
}



Wall::Wall(int x_location, int y_location, StudentWorld* temp):Actor(IID_WALL, x_location, y_location, 0, 0, 1, temp){}

bool Wall::isAlive(){
    return true;
}

void Wall::doSomething(){
    return;
}
