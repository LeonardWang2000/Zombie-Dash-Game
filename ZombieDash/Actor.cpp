#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, double x_location, double y_location, Direction dir, int depth, int size, StudentWorld* temp):GraphObject(imageID, x_location, y_location, dir, depth, size){
    moveTo(x_location, y_location);
    world = temp;
    alive = true;
    tickCount = 0;
    infectionStatus = false;
}
void Actor::pickUpGoodieIfAppropiate(Goodie *g){
    //does nothing
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
//does nothing
void Penelope::doSomething(){
    Human::doSomething();
}
void Penelope::doDifferentHumanStuff(){
        int ch;
        if (getWorld()->getKey(ch))
        {
            // user hit a key during this tick!
            switch (ch)
            {
                    //changes responses based on what key is hit
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
                    if(getLandmines() > 0){
                        getWorld()->addActor(new Landmine(getX(), getY(), getWorld()));
                        incrementLandmines(-1);
                    }
                    break;
                case KEY_PRESS_ENTER:
                    if(getVaccines() > 0){
                        incrementVaccines(-1);
                        setInfectionStatus(false);
                        setInfectionCount(0);
                    }
                    break;
                case KEY_PRESS_SPACE:
                    if(getFlameCharges() > 0){
                        incrementFlameCharges(-1);
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
                        int posx;
                        int posy;
                        for(int i = 1; i < 4; i++){
                            if(getDirection() == up){
                                posy = i * SPRITE_HEIGHT + getY();
                                posx = getX();
                            }else if(getDirection() == down){
                                posy = getY() - i * SPRITE_HEIGHT;
                                posx = getX();
                            }else if(getDirection() == right){
                                posx = getX() + i * SPRITE_WIDTH;
                                posy = getY();
                            }else{
                                posx = getX() - i * SPRITE_WIDTH;
                                posy = getY();
                            }
                            if(getWorld()->isFlameBlockedAt(posx, posy))
                                break;
                            else{
                                Flame* flame = new Flame(posx, posy, getDirection(), getWorld());
                                getWorld()->addActor(flame);
                            }
                        }
                    }
                    break;
                    // etc…
            }
        }
}
void Human::setInfectionCount(int count){
    infectionCount = 0;
}
Wall::Wall(double x_location, double y_location, StudentWorld* temp):Actor(IID_WALL, x_location, y_location, 0, 0, 1, temp){}
//do something for wall doesnt do anything

void Wall::doSomething(){
    return;
}


void Pit::doSomething(){
    getWorld()->activateOnAppropriateActors(this);
}

ActivatingObject::ActivatingObject(int imageID, double x_location, double y_location, Direction dir,int depth, StudentWorld* temp):Actor(imageID, x_location, y_location, dir, depth, 1, temp){
    
}

Exit::Exit(double x_location, double y_location, StudentWorld* temp):ActivatingObject(IID_EXIT, x_location, y_location, right, 0, temp){
    
}
//object doesnt do anything
void ActivatingObject::doSomething(){
    
}
Pit::Pit(double x_location, double y_location, StudentWorld* temp):ActivatingObject(IID_PIT, x_location, y_location, right, 0, temp){}

//initializes the correct variables in landmine
Landmine::Landmine(double x_location, double y_location, StudentWorld* temp):ActivatingObject(IID_LANDMINE, x_location, y_location, right, 1, temp){
    active = false;
    safetyTicks = 30;
}
void Landmine::activateIfAppropiate(Actor* a){
    if(a->triggersOnlyActiveLandmines()){
        activateLandmine();
    }
}
void Landmine::dieByFallOrBurnIfAppropriate(){
    if(isAlive())
        activateLandmine();
}
void Landmine::activateLandmine(){
    setDead();
    getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
    Flame* flame = new Flame(getX(), getY(), up, getWorld());
    //creates all the flames at the appropiate positions
    getWorld()->addActor(flame);
    getWorld()->addActor(new Flame(getX() - SPRITE_WIDTH, getY() + SPRITE_HEIGHT, up, getWorld()));
    getWorld()->addActor(new Flame(getX() - SPRITE_WIDTH, getY() - SPRITE_HEIGHT, up, getWorld()));
    getWorld()->addActor(new Flame(getX() - SPRITE_WIDTH, getY(), up, getWorld()));
    getWorld()->addActor(new Flame(getX() + SPRITE_WIDTH, getY(), up, getWorld()));
    getWorld()->addActor(new Flame(getX() + SPRITE_WIDTH, getY() + SPRITE_HEIGHT, up, getWorld()));
    getWorld()->addActor(new Flame(getX() + SPRITE_WIDTH, getY() - SPRITE_HEIGHT, up, getWorld()));
    getWorld()->addActor(new Flame(getX(), getY() + SPRITE_HEIGHT, up, getWorld()));
    getWorld()->addActor(new Flame(getX(), getY() - SPRITE_HEIGHT, up, getWorld()));
    getWorld()->addActor(new Pit(getX(), getY(), getWorld()));
}
void Landmine::doSomething(){
    if(!isAlive())
        return;
    if(!active){
        safetyTicks--;
        if(safetyTicks==0){
            active = true;
        }
        return;
    }
    //activates on the correct ones
    getWorld()->activateOnAppropriateActors(this);
}
bool Actor::triggersOnlyActiveLandmines(){
    return false;
}
bool Agent::triggersOnlyActiveLandmines(){
    return true;
}
//makes sure flames is working
Flame:: Flame(double x_location, double y_location, Direction dir, StudentWorld* temp):ActivatingObject(IID_FLAME, x_location, y_location, dir,0, temp){}
void Flame::doSomething(){
    if(!isAlive())
        return;
    incrementTickCount();
    if(getTickCount() == 2){
        setDead();
        return;
    }
        getWorld()->activateOnAppropriateActors(this);
}

void Actor::dieByFallOrBurnIfAppropriate(){
    //do nothing
}
void DumbZombie::dieByFallOrBurnIfAppropriate(){
    setDead();
    getWorld()->playSound(SOUND_ZOMBIE_DIE);
    getWorld()->increaseScore(1000);
    if(randInt(1, 10) == 1){
        switch(randInt(1, 4)){
            case(1):{
                if(!getWorld()->ifOneObjectOverlaps(getX() + SPRITE_WIDTH, getY())){
                    VaccineGoodie* vaccine = new VaccineGoodie(getX() + SPRITE_WIDTH, getY(), getWorld());
                    getWorld()->addActor(vaccine);
                }
                break;
            }
            case(2):{
                if(!getWorld()->ifOneObjectOverlaps(getX() - SPRITE_WIDTH, getY()))
                    getWorld()->addActor(new VaccineGoodie(getX() - SPRITE_WIDTH, getY(), getWorld()));
                break;
            }
            case(3):{
                if(!getWorld()->ifOneObjectOverlaps(getX(), getY() + SPRITE_HEIGHT))
                    getWorld()->addActor(new VaccineGoodie(getX(), getY() + SPRITE_HEIGHT, getWorld()));
                break;
            }
            case(4):{
                if(!getWorld()->ifOneObjectOverlaps(getX(), getY() - SPRITE_HEIGHT))
                    getWorld()->addActor(new VaccineGoodie(getX(), getY() - SPRITE_HEIGHT, getWorld()));
                break;
            }
        }
    }
}
//plays the correct sounds and does the right actions
void SmartZombie::dieByFallOrBurnIfAppropriate(){
    setDead();
    getWorld()->playSound(SOUND_ZOMBIE_DIE);
    getWorld()->increaseScore(2000);
}
void Citizen::dieByFallOrBurnIfAppropriate(){
    setDead();
    getWorld()->playSound(SOUND_CITIZEN_DIE);
    getWorld()->increaseScore(-1000);
}
void Penelope::dieByFallOrBurnIfAppropriate(){
    setDead();
    getWorld()->playSound(SOUND_PLAYER_DIE);
}
void Goodie::dieByFallOrBurnIfAppropriate(){
    setDead();
}
//checks vomit constructor
Vomit::Vomit(double x_location, double y_location, Direction dir, StudentWorld* temp):ActivatingObject(IID_VOMIT, x_location, y_location, dir, 0, temp){}
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
        a->setInfectionStatus(true);
    }
}

bool Actor::beVomitedOnIfAppropriate(){
    return false;
}
bool Human::beVomitedOnIfAppropriate(){
    return true;
}
void Actor::setInfectionStatus(bool status){
    infectionStatus = status;
}
//plays citizen sound
void Citizen::setInfectionStatus(bool status){
    if(getInfectionStatus())
        return;
    Actor::setInfectionStatus(status);
    getWorld()->playSound(SOUND_CITIZEN_INFECTED);
}


bool Actor::getInfectionStatus(){
    return infectionStatus;
}
//depth of goodie is always one, direction right
Goodie::Goodie(int imageID, double x_location, double y_location, StudentWorld* temp):ActivatingObject(imageID, x_location, y_location, right, 0, temp){}

VaccineGoodie::VaccineGoodie(double x_location, double y_location, StudentWorld* temp):Goodie(IID_VACCINE_GOODIE, x_location, y_location, temp){}

LandmineGoodie::LandmineGoodie(double x_location, double y_location, StudentWorld* temp):Goodie(IID_LANDMINE_GOODIE, x_location, y_location, temp){}

GasCanGoodie::GasCanGoodie(double x_location, double y_location, StudentWorld* temp):Goodie(IID_GAS_CAN_GOODIE, x_location, y_location, temp){}

void Goodie::activateIfAppropiate(Actor *temp){
    temp->pickUpGoodieIfAppropiate(this);
    dieByFallOrBurnIfAppropriate();
}
void Goodie::doSomething(){
    if(!isAlive())
        return;
    if(getWorld()->checkPlayerOverlap(getX(), getY(), 10, this)){
        getWorld()->increaseScore(50);
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
    }
}
//gives the goodies accordingly
void VaccineGoodie::giveGoodies(Penelope *p){
    p->incrementVaccines(1);
}
void GasCanGoodie::giveGoodies(Penelope *p){
    p->incrementFlameCharges(5);
}
void LandmineGoodie::giveGoodies(Penelope *p){
    p->incrementLandmines(2);
}
int Penelope::getVaccines(){
    return vaccines;
}
int Penelope::getLandmines(){
    return landmines;
}
int Penelope::getFlameCharges(){
    return flamethrowerCount;
}
void Agent::getDamage(){
    setDead();
    //PLAY THE CORRECT MOTHERFUCKING SOUNDS DEPENDING ON WHO GODDAM DIED, PLAYER AND CITIZEN DIFFERENTIATION
}

//HUMANS--------------------------
Human::Human(int imageID, double x_location, double y_location, StudentWorld* temp):Agent(imageID, x_location, y_location, temp){
    infectionCount = 0;
}
void Penelope::pickUpGoodieIfAppropiate(Goodie* g){
    g->giveGoodies(this);
}
Penelope::Penelope(double x_location, double y_location, StudentWorld* temp):Human(IID_PLAYER, x_location, y_location, temp){
    flamethrowerCount = 0;
    vaccines = 0;
    landmines = 0;
}
//increment each of them accordingly
void Penelope::incrementVaccines(int amt){
    vaccines+=amt;
}

void Penelope::incrementLandmines(int amt){
    landmines+=amt;
}

void Penelope::incrementFlameCharges(int amt){
    flamethrowerCount+=amt;
}

Citizen::Citizen(double x_location, double y_location, StudentWorld* temp):Human(IID_CITIZEN, x_location, y_location, temp){}

bool Actor::isHuman(){
    return false;
}
//test if the humans is true
bool Human::isHuman(){
    return true;
}

bool Penelope::isHuman(){
    return true;
}

Agent::Agent(int imageID, double x_location, double y_location, StudentWorld* temp):Actor(imageID, x_location, y_location, 0, 0, 1, temp){
    
}
//adds vomit when it needs to be added
bool Zombie::addVomitIfAppropiate(double vomit_x, double vomit_y){
    if(getWorld()->isZombieVomitTriggerAt(vomit_x, vomit_y)){
        Vomit* vomit = new Vomit(vomit_x, vomit_y, up, getWorld());
        getWorld()->addActor(vomit);
        getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
        return true;
    }
        if(getWorld()->checkPlayerOverlap(vomit_x, vomit_y, 10, this) || getWorld()->checkCitizenOverlap(this, 10)){
            if(randInt(1, 3) == 1){
                Vomit* vomit = new Vomit(vomit_x, vomit_y, up, getWorld());
                getWorld()->addActor(vomit);
                getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
                return true;
            }
        }
    return false;
}
void DumbZombie::doDifferentZombieStuff(){
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
    //checks directions effeciently without wasting code
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
void DumbZombie::doSomething(){
    Zombie::doSomething();
}

void Zombie::doSomething(){
    //common cases in both zombie classes
    if(!isAlive())
        return;
    incrementTickCount();
    if(getTickCount()%2==0){
        return;
    }
    //vomit cases
    switch(getDirection()){
        case up:
            addVomitIfAppropiate(getX(), getY()+16);
            break;
        case down:
            addVomitIfAppropiate(getX(), getY()-16);
            break;
        case left:
            addVomitIfAppropiate(getX()-16, getY());
            break;
        case right:
            addVomitIfAppropiate(getX()+16, getY());
            break;

    }
    doDifferentZombieStuff();
}
//does something different for zombies
void SmartZombie::doDifferentZombieStuff(){
    double xOfClosest;
    double yOfClosest;
    getWorld()->closestHuman(xOfClosest, yOfClosest, this);
    if(getMovementPlan() == 0){
        setMovementPlan(randInt(3, 10));
        if(!getWorld()->checkObjectOverlap(xOfClosest, yOfClosest, this, 80)){
            switch(randInt(0, 3)){
                    //random directions
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
        }else{
            if(getX() == xOfClosest || getY() == yOfClosest){
                //if same row
                if(getX() == xOfClosest){
                    //if if citizen/penelope is above
                    if(yOfClosest > getY()){
                        //if we can move up
                        setDirection(up);
                    }else if(yOfClosest < getY()){
                        //if citizen/penelope is below and we can move there
                        setDirection(down);
                    }
                    
                }
                if(getY() == yOfClosest){
                    //if citizen/penelope is on the right
                    if(xOfClosest > getX()){
                        setDirection(right);
                    }else if(xOfClosest < getX()){
                        //if citizen/penelope is on the left
                        setDirection(left);
                    }
                }
            }
            //checks if not same row or col
            if(getX() != xOfClosest && getY() != yOfClosest){
                int yChange = 0;
                int xChange = 0;
                if(yOfClosest > getY())
                    yChange = up;
                else
                    yChange = down;
                if(xOfClosest > getX())
                    xChange = right;
                else
                    xChange = left;
                if(randInt(0, 1) == 0){
                    setDirection(yChange);
                }
                else{
                    setDirection(xChange);
                }
                
            }
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
Zombie::Zombie(double x_location, double y_location, StudentWorld* temp):Agent(IID_ZOMBIE, x_location, y_location, temp){
    movementPlan = 0;
}

SmartZombie::SmartZombie(double x_location, double y_location, StudentWorld* temp):Zombie(x_location, y_location, temp){
    
}// a lot of these constructors dont do anything besides intializer list

DumbZombie::DumbZombie(double x_location, double y_location, StudentWorld* temp):Zombie(x_location, y_location, temp){
    
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


int Human::getInfectionCount(){
    return infectionCount;
}
void Human::incrementInfectionCount(){
    infectionCount++;
}

void Human::doSomething(){
    if(!isAlive()){
        return;
    }
    if(getInfectionStatus()){
        incrementInfectionCount();
        if(getInfectionCount() == 500){
            setDead();
            getWorld()->increaseScore(-1000);
            playAppropiateSound();
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
    doDifferentHumanStuff();
}
//plays the right sound
void Citizen::playAppropiateSound(){
    getWorld()->playSound(SOUND_ZOMBIE_BORN);
}
void Penelope::playAppropiateSound(){
    getWorld()->playSound(SOUND_PLAYER_DIE);
}
void Citizen::doDifferentHumanStuff(){
    double dist_p = getWorld()->distanceToPlayer(getX(), getY());
    double dist_z = getWorld()->leastDistanceToZombie(getX(), getY());
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
        //checks for different rows and cols
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
    //what happens if zombies distance less than 80
    if(dist_z <= 80){
        double farthestDistance = getWorld()->leastDistanceToZombie(getX(), getY());
        int tempDirection = -1;
        if(isAgentFreeDirection(getX()+2, getY())){
            if(getWorld()->leastDistanceToZombie(getX()+2, getY()) > farthestDistance){
                farthestDistance = getWorld()->leastDistanceToZombie(getX()+2, getY());
                tempDirection = right;
            }
        }if(isAgentFreeDirection(getX()-2, getY())){
            if(getWorld()->leastDistanceToZombie(getX()-2, getY()) > farthestDistance){
                farthestDistance = getWorld()->leastDistanceToZombie(getX()-2, getY());
                tempDirection = left;
            }
        }if(isAgentFreeDirection(getX(), getY()-2)){
            if(getWorld()->leastDistanceToZombie(getX(), getY()-2) > farthestDistance){
                farthestDistance = getWorld()->leastDistanceToZombie(getX(), getY()-2);
                tempDirection = down;
            }
        }if(isAgentFreeDirection(getX(), getY()+2)){
            if(getWorld()->leastDistanceToZombie(getX(), getY()+2) > farthestDistance){
                farthestDistance = getWorld()->leastDistanceToZombie(getX(), getY()+2);
                tempDirection = up;
            }
        }
        if(tempDirection >= 0){
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
void Citizen::doSomething(){
    Human::doSomething();
}

bool Agent::isAgentFreeDirection(double x, double y){
    if(getWorld()->checkPositionFree(x, y, this) && getWorld()->checkPositionFreePlayer(x, y))
        return true;
    return false;
}
//helps add the two pixels to the correct randomized direction
double Agent:: appropiateMovementDirection(int change, double distance){
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
void Pit::activateIfAppropiate(Actor *a){
    a->dieByFallOrBurnIfAppropriate();
}
void Flame::activateIfAppropiate(Actor *temp){
    temp->dieByFallOrBurnIfAppropriate();
}
void Actor::incrementTickCount(){
    tickCount++;
}
//getter functions
int Actor::getTickCount(){
    return tickCount;
}

bool Actor::isZombie(){
    return false;
}

bool Zombie::isZombie(){
    return true;
}
void Actor::activateIfAppropiate(Actor *a){
    //nothing
}
void Actor::useExitIfAppropriate(){}
void Citizen::useExitIfAppropriate(){
    setDead();
    getWorld()->playSound(SOUND_CITIZEN_SAVED);
    getWorld()->increaseScore(500);
}
void Penelope::useExitIfAppropriate(){
    if(!getWorld()->isCitizenLeft()){
        getWorld()->setLevelDone();
    }
}
void Exit::doSomething(){
    //set citizen to dead
    getWorld()->checkCitizenOverlap(this, 10);
    getWorld()->checkPlayerOverlap(getX(), getY(), 10, this);
}

void Exit::activateIfAppropiate(Actor *a){
    a->useExitIfAppropriate();
}

void Zombie::setMovementPlan(int plan){
    movementPlan = plan;
}
//getters and setters
int Zombie::getMovementPlan(){
    return movementPlan;
}
bool Actor::blocksFlame() const{
    return false;
}
bool Exit::blocksFlame() const{
    return true;
}
bool Wall::blocksFlame() const{
    return true;
}

