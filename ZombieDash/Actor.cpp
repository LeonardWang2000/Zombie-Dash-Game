#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
void Actor::doSomething(){
    
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
                    if(getWorld()->checkPositionFree(getX(), getY())){
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
