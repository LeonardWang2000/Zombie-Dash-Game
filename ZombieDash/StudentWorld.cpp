#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    score = 0;
    levelDone = false;
}

int StudentWorld::init()
{
    //first 0 represents right direction
    levelDone = false;
    setUpLevel();
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    // The term "actors" refers to all zombies, Penelope, goodies,
    // pits, flames, vomit, landmines, etc.
    // Give each actor a chance to do something, including Penelope
    ostringstream oss;
    oss << "Score: " << getScore() << "  Level: " << getLevel() << "  Lives: " << getLives() << "  Vacc:  " << "?" << "   Flames: ?  " << "  Mines:  ?  " << "  Infected:   ?";
    string s = oss.str();
    setGameStatText(s);
    for(int i = 0; i< allActors.size(); i++)
    {
        if (allActors[i]->isAlive())
        {
            // tell each actor to do something (e.g. move)
            player->doSomething();
            allActors[i]->doSomething();
            if (!player->isAlive()){
                return GWSTATUS_PLAYER_DIED;
            }
//            if (Penelope completed the current level)
//                return GWSTATUS_FINISHED_LEVEL;
            if(levelDone)
                return GWSTATUS_FINISHED_LEVEL;
        }
    }
    // Remove newly-dead actors after each tick
    vector<Actor*>::iterator it;
    for(it = allActors.begin(); it != allActors.end(); it++){
        if(!(*it)->isAlive()){
            delete *it;
            allActors.erase(it);
            it = allActors.begin();
        }
    }
    // Update the game status line
    //Update Display Text // update the score/lives/level text at screen top
    // the player hasn’t completed the current level and hasn’t died, so
    // continue playing the current level
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    //delete everything including player
    delete player;
    vector<Actor*>::iterator it;
    for(it = allActors.begin(); it != allActors.end(); it++){
        delete *it;
        allActors.erase(it);
        it = allActors.begin();
    }
}
StudentWorld::~StudentWorld(){
    cleanUp();
}

bool StudentWorld::checkPositionFree(double x, double y, Actor* temp){
    double x_distance;
    double y_distance;
    for(int i = 0; i < allActors.size(); i++){
        x_distance = allActors[i]->getX()+SPRITE_WIDTH-1;
        y_distance = allActors[i]->getY()+SPRITE_HEIGHT-1;
        if(temp->getX() == allActors[i]->getX() && temp->getY() == allActors[i]->getY()){
            continue;
        }
        if((x <= x_distance) && x+SPRITE_WIDTH-1 >= allActors[i]->getX() && (y <= y_distance) && y+SPRITE_HEIGHT-1 >= allActors[i]->getY() && !allActors[i]->canBeMovedOnto()){
            return false;
        }
    }
    
    return true;
}

bool StudentWorld::checkPositionFreePlayer(double x, double y){
    if((x <= player->getX() + SPRITE_WIDTH-1) && x+SPRITE_WIDTH-1 >= player->getX() && (y <= player->getY() + SPRITE_HEIGHT-1) && y+SPRITE_HEIGHT-1 >= player->getY()){
        return false;
    }
    return true;
}

//x represents x value you want to goto, actor is this actor
bool StudentWorld::checkObjectOverlap(double x, double y, Actor* temp, int overlap){
    
    
    double centerX = (temp->getX()) - x;
    double centerY = (temp->getY()) - y;
    double distance = sqrt(centerX*centerX + centerY*centerY);
    if(distance <= overlap){
        return true;
    }
    return false;
}

bool StudentWorld::checkPlayerOverlap(double x, double y, int overlap, Actor* temp){
    if(checkObjectOverlap(x, y, player, overlap)){
        temp->activateIfAppropiate(player);
        return true;
    }
    return false;
}

void StudentWorld::closestHuman(double &x, double &y, Actor *temp){
    double leastDistance = 1000;
    for(int i = 0; i < allActors.size(); i++){
        if(allActors[i]->isHuman()){
            if(distanceToActor(temp->getX(), allActors[i]->getX(), temp->getY(), allActors[i]->getY()) < leastDistance){
                leastDistance = distanceToActor(temp->getX(), allActors[i]->getX(), temp->getY(), allActors[i]->getY());
                x = allActors[i]->getX();
                y = allActors[i]->getY();
            }
        }
    }
    if(distanceToPlayer(temp->getX(), temp->getY()) < leastDistance){
        x = player->getX();
        y = player->getY();
    }
  
}

bool StudentWorld::checkCitizenOverlap(Actor *temp, int overlap){
    for(int i = 0; i < allActors.size(); i++){
        if(allActors[i]->isHuman()){
            if(checkObjectOverlap(temp->getX(), temp->getY(), allActors[i], overlap)){
                temp->activateIfAppropiate(allActors[i]);
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::isZombieVomitTriggerAt(double x, double y) const{
    for(int i = 0; i < allActors.size(); i++){
        if(allActors[i]->getX() == x && allActors[i]->getY() == y && allActors[i]->isHuman())
            return true;
    }
    if(player->getX() == x && player->getY() == y)
        return true;
    return false;
}

bool StudentWorld::isCitizenLeft(){
    for(int i = 0; i < allActors.size(); i++){
        if(allActors[i]->isHuman())
            return true;
    }
    return false;
}

double StudentWorld::distanceToPlayer(double x, double y){
    return distanceToActor(x, player->getX(), y, player->getY());
}
//change the check overlap functions
void StudentWorld::activateOnAppropriateActors(Actor* a){
    a->activateIfAppropiate(a);
}


double StudentWorld::distanceToActor(double x1, double x2, double y1, double y2){
    double x = x1-x2;
    double y = y1-y2;
    return sqrt(x*x + y*y);
}

//make a distance to specific actor instance method to call if multiple distance to things need to be called
double StudentWorld::leastDistanceToZombie(double x, double y){
    double leastDistance = 1000;
    for(int i = 0; i < allActors.size(); i++){
        if(allActors[i]->isZombie()){
            if(distanceToActor(x, allActors[i]->getX(), y, allActors[i]->getY()) < leastDistance){
                leastDistance = distanceToActor(x, allActors[i]->getX(), y, allActors[i]->getY());
        }
    }
    }
    return leastDistance;
}



void StudentWorld::addActor(Actor *a){
    allActors.push_back(a);
}

int StudentWorld::getPenelopeX(){
    return player->getX();
}

int StudentWorld::getPenelopeY(){
    return player->getY();
}

void StudentWorld::setLevelDone(){
    levelDone = true;
}
int StudentWorld::getScore(){
    return score;
}
void StudentWorld::addToScore(int number){
    score += number;
}
void StudentWorld::setUpLevel(){
//    only works up to ten levels
//    ostringstream oss;
//    oss << "level0" << getLevel() << ".txt";
//    string s = oss.str();
    Level lev(assetPath());
//    string levelFile = s;
    //temp test
    string levelFile = "level01.txt";
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        cerr << "Cannot find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        for(int i = 0; i < SPRITE_WIDTH; i++){
            for(int j = 0; j < SPRITE_HEIGHT; j++){
                Level::MazeEntry ge = lev.getContentsOf(i,j); // level_x=5, level_y=10
                switch (ge) // so x=80 and y=160
                {
                    case Level::empty:{
                        break;
                    }
                    case Level::smart_zombie:{
                        Zombie* smartZombie = new SmartZombie(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                        allActors.push_back(smartZombie);
                        break;
                    }
                    case Level::dumb_zombie:{
                        Zombie* dumbZombie = new DumbZombie(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                        allActors.push_back(dumbZombie);
                        break;
                    }
                    case Level::citizen:{
                        Citizen* citizen = new Citizen( i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                        allActors.push_back(citizen);
                        break;
                    }
                    case Level::player:{
                        player = new Penelope(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                        break;
                    }
                    case Level::exit:{
                        Exit* exit = new Exit(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                        allActors.push_back(exit);
                        break;
                    }
                    case Level::wall:{
                        Wall* wall = new Wall(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                        allActors.push_back(wall);
                        break;
                    }
                    case Level::pit:{
//                        Pit* pit = new Pit
//                        allActors.push_back(pit);
                        break;
                    }
                        // etc…
                }
            }
        }
    }
}
