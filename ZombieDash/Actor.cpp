#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, int x_location, int y_location, Direction dir, int depth, double size, StudentWorld* temp):GraphObject(imageID, x_location, y_location, dir, depth, size){
    moveTo(x_location, y_location);
    world = temp;
    alive = true;
    tickCount = 0;
    infectionStatus = false;
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

ActivatingObject::ActivatingObject(int imageID, int x_location, int y_location, Direction dir, StudentWorld* temp):Actor(imageID, x_location, y_location, dir, 0, 1, temp){
    
}

Exit::Exit(int x_location, int y_location, StudentWorld* temp):ActivatingObject(IID_EXIT, x_location, y_location, right, temp){
    
}

void ActivatingObject::doSomething(){
    
}
//Pit::Pit(int x_location, int y_location, StudentWorld* temp):Actor(IID_PIT, x_location, y_location, 0, 0, 1, temp){}
//
//Flame:: Flame(int x_location, int y_location, StudentWorld* temp):Actor(IID_FLAME, x_location, y_location, right, 0, 1, temp){}
//
Vomit::Vomit(int x_location, int y_location, Direction dir, StudentWorld* temp):ActivatingObject(IID_VOMIT, x_location, y_location, dir, temp){}
void Vomit::doSomething(){
    if(!isAlive()){
        return;
    }
    incrementTickCount();
    if(getTickCount() == 2){
        setDead();
        return;
    }
    if(getWorld()->checkPlayerOverlap(getX(), getY(), 10, this) || getWorld()->checkCitizenOverlap(this, 10)){
        //gets infected through activated
    }
        
}
void Vomit::activateIfAppropiate(Actor *a){
    if(a->isHuman()){
        a->setInfectionStatus();
    }
    
}

bool Actor::beVomitedOnIfAppropriate(){
    return false;
}
bool Human::beVomitedOnIfAppropriate(){
    return true;
}
void Actor::setInfectionStatus(){
    infectionStatus = true;
}
bool Actor::getInfectionStatus(){
    return infectionStatus;
}
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
void DumbZombie::doSomething(){
    if(!isAlive())
        return;
    incrementTickCount();
    if(getTickCount()%2==0){
        return;
    }
//    if(getDirection() == up && getY() < )
    //IMPLEMENT STEP 3, VOMIT SHIT
    if(getMovementPlan() == 0){
        setMovementPlan(randInt(3, 10));
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
        if(isAgentFreeDirection(getX() + appropiateMovementDirection(getDirection(), 1), getY())){
            moveTo(getX() + appropiateMovementDirection(getDirection(), 1), getY());
            setMovementPlan(getMovementPlan()-1);
            return;
        }
    }else if(getDirection() == up || getDirection() == down){
        if(isAgentFreeDirection(getX(), getY() + appropiateMovementDirection(getDirection(), 1))){
            moveTo(getX(), getY()+ appropiateMovementDirection(getDirection(), 1));
            setMovementPlan(getMovementPlan()-1);
            return;
        }
    }
    setMovementPlan(0);
}

void Zombie::doSomething(){
    
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
        //set citizen to dead
    if(getWorld()->checkCitizenOverlap(this, 10)){
        //set the citizen to dead in the function above^
        getWorld()->increaseScore(500);
        getWorld()->playSound(SOUND_CITIZEN_SAVED);
    }
    if(!getWorld()->isCitizenLeft() && getWorld()->checkPlayerOverlap(getX(), getY(), 10, this))
        getWorld()->setLevelDone();
}
int Human::getInfectionCount(){
    return infectionCount;
}
void Human::incrementInfectionCount(){
    infectionCount++;
}
void Citizen::doSomething(){
    if(!isAlive()){
        return;
    }
    if(getInfectionStatus()){
        incrementInfectionCount();
        if(getInfectionCount() == 500){
            setDead();
            getWorld()->playSound(SOUND_ZOMBIE_BORN);
            getWorld()->addToScore(-1000);
            int rand = randInt(1, 10);
            if(rand >= 1 && rand <= 3){
                SmartZombie* zombie = new SmartZombie(getX(), getY(), getWorld());
                getWorld()->addActor(zombie);
                return;
            }else{
                DumbZombie* zombie = new DumbZombie(getX(), getY(), getWorld());
                getWorld()->addActor(zombie);
                return;
            }
        }
    }
    incrementTickCount();
    if(getTickCount()%2==0){
        return;
    }
    int dist_p = getWorld()->distanceToPlayer(getX(), getY());
    int dist_z = getWorld()->distanceToZombie(getX(), getY());
    if(dist_p < dist_z && dist_p <= 80){
        if(getX() == getWorld()->getPenelopeX() || getY() == getWorld()->getPenelopeY()){
        //if same row
        if(getX() == getWorld()->getPenelopeX()){
            //if if penelope is above
            if(getWorld()->getPenelopeY() > getY()){
                //if we can move up
                if(getWorld()->checkPositionFree(getX(), getY()+2, this) && getWorld()->checkPositionFreePlayer(getX(), getY()+2)){
                    setDirection(up);
                    moveTo(getX(), getY()+2);
                    return;
                }
            }else{
                //if penelope is below and we can move there
                if(getWorld()->checkPositionFree(getX(), getY()-2, this) && getWorld()->checkPositionFreePlayer(getX(), getY()-2)){
                    setDirection(down);
                    moveTo(getX(), getY()-2);
                    return;
                }
            }
                
        }
        if(getY() == getWorld()->getPenelopeY()){
            //if penelope is on the right
            if(getWorld()->getPenelopeX() > getX()){
                if(getWorld()->checkPositionFree(getX()+2, getY(), this) && getWorld()->checkPositionFreePlayer(getX()+2, getY())){
                    setDirection(right);
                    moveTo(getX()+2, getY());
                    return;
                }
            }else{
                //if penelope is on the left
                if(getWorld()->checkPositionFree(getX()-2, getY(), this) && getWorld()->checkPositionFreePlayer(getX()-2, getY())){
                    setDirection(left);
                    moveTo(getX()-2, getY());
                    return;
                }
            }
        }
        }
        if(getX() != getWorld()->getPenelopeX() && getY() != getWorld()->getPenelopeY()){
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
            if(isAgentFreeDirection(getX(), getY() + appropiateMovementDirection(yChange, 2))){
                setDirection(yChange);
                moveTo(getX(), getY()+appropiateMovementDirection(yChange, 2));
                return;
            }else{
                if(isAgentFreeDirection(getX() + appropiateMovementDirection(xChange, 2), getY())){
                    setDirection(xChange);
                    moveTo(getX() + appropiateMovementDirection(xChange, 2), getY());
                    return;
                }
            }
                
        }
        else{
            if(isAgentFreeDirection(getX() + appropiateMovementDirection(xChange, 2), getY())){
                setDirection(xChange);
                moveTo(getX() + appropiateMovementDirection(xChange, 2), getY());
                return;
            }else{
                if(isAgentFreeDirection(getX(), getY() + appropiateMovementDirection(yChange, 2))){
                    setDirection(yChange);
                    moveTo(getX(), getY()+appropiateMovementDirection(yChange, 2));
                    return;
                }
            }
        }
        
    }
    }
    if(dist_z <= 80){
        int farthestDistance = getWorld()->distanceToZombie(getX(), getY());
        int tempDirection = -1;
        if(isAgentFreeDirection(getX()+2, getY())){
            if(getWorld()->distanceToZombie(getX()+2, getY()) > farthestDistance){
                farthestDistance = getWorld()->distanceToZombie(getX()+2, getY());
            }
        }if(isAgentFreeDirection(getX()-2, getY())){
            if(getWorld()->distanceToZombie(getX()-2, getY()) > farthestDistance){
                farthestDistance = getWorld()->distanceToZombie(getX()-2, getY());
                tempDirection = left;
            }
        }if(isAgentFreeDirection(getX(), getY()-2)){
            if(getWorld()->distanceToZombie(getX(), getY()-2) > farthestDistance){
                farthestDistance = getWorld()->distanceToZombie(getX(), getY()-2);
                tempDirection = down;
            }
        }if(isAgentFreeDirection(getX(), getY()+2)){
            if(getWorld()->distanceToZombie(getX(), getY()+2) > farthestDistance){
                farthestDistance = getWorld()->distanceToZombie(getX(), getY()+2);
                tempDirection = up;
            }
        }
        if(tempDirection > 0){
            setDirection(tempDirection);
            if(tempDirection == up || tempDirection == down){
                moveTo(getX(), getY() + appropiateMovementDirection(tempDirection, 2));
                return;
            }
            else if(tempDirection == left || tempDirection == right){
                moveTo(getX() + appropiateMovementDirection(tempDirection, 2), getY());
                return;
            }
        }
    }
}

bool Agent::isAgentFreeDirection(int x, int y){
    if(getWorld()->checkPositionFree(x, y, this) && getWorld()->checkPositionFreePlayer(x, y))
        return true;
    return false;
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
    if(getWorld()->isCitizenLeft()){
        a->setDead();
        return;
    }
    getWorld()->setLevelDone();
    
}

void Zombie::setMovementPlan(int plan){
    movementPlan = plan;
}

int Zombie::getMovementPlan(){
    return movementPlan;
}
