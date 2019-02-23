#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int x_location, int y_location, Direction dir, int depth, double size, StudentWorld* temp):GraphObject(imageID, x_location, y_location, dir, depth, size){
    moveTo(x_location, y_location);
    world = temp;
    alive = true;
    tickCount = 0;
}
void Actor::doSomething(){
    return;
}
void Actor::setDead(){
    alive = false;
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
                    if(getWorld()->checkPositionFree(getX()-4, getY(), this)){
                        moveTo(getX()-4, getY());
                    }
                    break;
                case KEY_PRESS_RIGHT:
                    setDirection(right);
                    if(getWorld()->checkPositionFree(getX()+4, getY(), this))
                        moveTo(getX()+4, getY());
                    break;
                case KEY_PRESS_UP:
                    setDirection(up);
                    if(getWorld()->checkPositionFree(getX(), getY()+4, this))
                        moveTo(getX(), getY()+4);
                    break;
                case KEY_PRESS_DOWN:
                    setDirection(down);
                    if(getWorld()->checkPositionFree(getX(), getY()-4, this))
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







Wall::Wall(int x_location, int y_location, StudentWorld* temp):Actor(IID_WALL, x_location, y_location, 0, 0, 1, temp){}


void Wall::doSomething(){
    return;
}

void Flame::doSomething(){
    
}
void Pit::doSomething(){
    
}
void Vomit::doSomething(){
    
}


Exit::Exit(int x_location, int y_location, StudentWorld* temp):Actor(IID_EXIT, x_location, y_location, 0, 0, 1, temp){}


//Pit::Pit(int x_location, int y_location, StudentWorld* temp):Actor(IID_PIT, x_location, y_location, 0, 0, 1, temp){}
//
//Flame:: Flame(int x_location, int y_location, StudentWorld* temp):Actor(IID_FLAME, x_location, y_location, right, 0, 1, temp){}
//
//Vomit::Vomit(int x_location, int y_location, Direction dir, StudentWorld* temp):Actor(IID_VOMIT, x_location, y_location, dir, 0, 1, temp){}

//depth of goodie is always one, direction right
//Goodie::Goodie(int imageID, int x_location, int y_location, StudentWorld* temp):ActivatingObject(imageID, x_location, y_location, temp){
//    
//}

void Agent::getDamage(){
    setDead();
}

//HUMANS--------------------------
Human::Human(int imageID, int x_location, int y_location, StudentWorld* temp):Agent(imageID, x_location, y_location, temp){
    infectionCount = 0;
    infectionStatus = false;
}

Penelope::Penelope(int x_location, int y_location, StudentWorld* temp):Human(IID_PLAYER, x_location, y_location, temp){
    numberOfLives = 3;
}

Citizen::Citizen(int x_location, int y_location, StudentWorld* temp):Human(IID_CITIZEN, x_location, y_location, temp){
    
}

bool Actor::isHuman(){
    return false;
}

bool Human::isHuman(){
    return true;
}

bool Penelope::isHuman(){
    //need to be false until all citizens are gone
    return true;
}

Agent::Agent(int imageID, int x_location, int y_location, StudentWorld* temp):Actor(imageID, x_location, y_location, 0, 0, 1, temp){
    
}

Zombie::Zombie(int x_location, int y_location, StudentWorld* temp):Agent(IID_ZOMBIE, x_location, y_location, temp){
    
}

SmartZombie::SmartZombie(int x_location, int y_location, StudentWorld* temp):Zombie(x_location, y_location, temp){
    
}

DumbZombie::DumbZombie(int x_location, int y_location, StudentWorld* temp):Zombie(x_location, y_location, temp){
    
}

bool Agent::canBeMovedOnto(){
    return false;
}



bool Actor::canBeMovedOnto(){
    return true;
}

bool Wall::canBeMovedOnto(){
    return false;
}

void Exit::doSomething(){
//    if(getWorld()->checkCitizenOverlap(this))
//        //set citizen to dead
    if(!getWorld()->isCitizenLeft() && getWorld()->checkPlayerOverlap(this))
        getWorld()->setLevelDone();
}

void Citizen::doSomething(){
    if(!isAlive()){
        return;
    }
    incrementTickCount();
    if(getTickCount()%2==0){
        return;
    }
    int dist_p = getWorld()->distanceToPlayer(this);
    int dist_z = getWorld()->distanceToZombie(this);
    if(dist_p < dist_z && dist_p <= 80){
        //if same row
        if(getX() == getWorld()->getPenelopeX()){
            //if if penelope is above
            if(getWorld()->getPenelopeY() > getY()){
                //if we can move up
                if(getWorld()->checkPositionFree(getX(), getY()+2, this)){
                    setDirection(up);
                    moveTo(getX(), getY()+2);
                    return;
                }
            }else{
                //if penelope is below and we can move there
                if(getWorld()->checkPositionFree(getX(), getY()-2, this)){
                    setDirection(down);
                    moveTo(getX(), getY()-2);
                    return;
                }
            }
                
        }
        if(getY() == getWorld()->getPenelopeY()){
            //if penelope is on the right
            if(getWorld()->getPenelopeX() > getX()){
                if(getWorld()->checkPositionFree(getX()+2, getY(), this)){
                    setDirection(right);
                    moveTo(getX()+2, getY());
                    return;
                }
            }else{
                //if penelope is on the left
                if(getWorld()->checkPositionFree(getX()-2, getY(), this)){
                    setDirection(left);
                    moveTo(getX()-2, getY());
                    return;
                }
            }
        }
    }
}

void Actor::incrementTickCount(){
    tickCount++;
}

int Actor::getTickCount(){
    return tickCount;
}

bool Actor::isZombie(){
    return false;
}

bool Zombie::isZombie(){
    return true;
}
