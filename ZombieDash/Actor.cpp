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
ActivatingObject::ActivatingObject(int imageID, int x_location, int y_location, StudentWorld* temp):Actor(imageID, x_location, y_location, 0, 0, 1, temp){
    
}

Exit::Exit(int x_location, int y_location, StudentWorld* temp):ActivatingObject(IID_EXIT, x_location, y_location, temp){
    
}

void ActivatingObject::doSomething(){
    
}
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
void Zombie::doSomething(){
    if(!isAlive())
        return;
    incrementTickCount();
    if(getTickCount()%2==0)
        return;
    //IMPLEMENT STEP 3, VOMIT SHIT
    if(movementPlan == 0){
        movementPlan = randInt(3, 10);
        switch(randInt(0, 3)){
            case 0:
                setDirection(right);
                break;
            case 1:
                setDirection(up);
                break;
            case 2:
                setDirection(left);
                break;
            case 3:
                setDirection(down);
                break;
        }
    }
    if(getDirection() == right || getDirection() == left){
        if(getWorld()->checkPositionFree(getX() + appropiateMovementDirection(getDirection(), 1), getY(), this)){
            moveTo(getX() + appropiateMovementDirection(getDirection(), 1), getY());
            movementPlan--;
            return;
        }
    }else if(getDirection() == up || getDirection() == down){
        if(getWorld()->checkPositionFree(getX(), getY()+ appropiateMovementDirection(getDirection(), 1), this)){
            moveTo(getX(), getY()+ appropiateMovementDirection(getDirection(), 1));
            movementPlan--;
            return;
        }
    }
    movementPlan = 0;
}

void DumbZombie::doSomething(){
    
}
Zombie::Zombie(int x_location, int y_location, StudentWorld* temp):Agent(IID_ZOMBIE, x_location, y_location, temp){
    movementPlan = 0;
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
    if(getWorld()->checkCitizenOverlap(this)){
        //set the citizen to dead in the function above^
        getWorld()->increaseScore(500);
        getWorld()->playSound(SOUND_CITIZEN_SAVED);
    }
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
        if(getX() == getWorld()->getPenelopeX() || getY() == getWorld()->getPenelopeY()){
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
        //NEED TO FIX CITIZEN RUNNING ONTO PENELOPE
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
        int yChange;
        int xChange;
        if(getWorld()->getPenelopeY() > getY())
            yChange = up;
        else
            yChange = down;
        if(getWorld()->getPenelopeX() > getX())
            xChange = right;
        else
            xChange = left;
        if(randInt(0, 1) == 0){
            if(getWorld()->checkPositionFree(getX(), getY() + appropiateMovementDirection(yChange, 2), this)){
                setDirection(yChange);
                moveTo(getX(), getY()+appropiateMovementDirection(yChange, 2));
                return;
            }else{
                if(getWorld()->checkPositionFree(getX() + appropiateMovementDirection(xChange, 2), getY(), this)){
                    setDirection(xChange);
                    moveTo(getX() + appropiateMovementDirection(xChange, 2), getY());
                    return;
                }
            }
                
        }
        else{
            if(getWorld()->checkPositionFree(getX() + appropiateMovementDirection(xChange, 2), getY(), this)){
                setDirection(xChange);
                moveTo(getX() + appropiateMovementDirection(xChange, 2), getY());
                return;
            }else{
                if(getWorld()->checkPositionFree(getX(), getY() + appropiateMovementDirection(yChange, 2), this)){
                    setDirection(yChange);
                    moveTo(getX(), getY()+appropiateMovementDirection(yChange, 2));
                    return;
                }
            }
        }
        
    }
}
//helps add the two pixels to the correct randomized direction
int Agent:: appropiateMovementDirection(int change, int distance){
    switch(change){
        case right:
        case up:
            return distance;
            break;
        case left:
        case down:
            return distance*-1;
            break;
    }
    return 0;
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
//ALL ACTIVATE TO APPROPIATE METHODS
void Actor::activateIfAppropiate(Actor *a){
    
}

void Exit::activateIfAppropiate(Actor *a){
    a->setDead();
}
