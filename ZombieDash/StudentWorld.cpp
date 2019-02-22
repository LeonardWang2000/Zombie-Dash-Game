#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
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
}

int StudentWorld::init()
{
    //first 0 represents right direction
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
        }
        // Remove newly-dead actors after each tick CHECK THIS, MIGHT NOT WORK AND NEED TO MAKE A SEPARATE FOR LOOP
        if(!allActors[i]->isAlive()){
            delete allActors[i];
            allActors.erase(allActors.begin()+i);
        }
    }
    // Remove newly-dead actors after each tick
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

bool StudentWorld::checkPositionFree(int x, int y){
    int x_distance;
    int y_distance;
    for(int i = 0; i < allActors.size(); i++){
        
        x_distance = allActors[i]->getX()+SPRITE_WIDTH-1;
        y_distance = allActors[i]->getY()+SPRITE_HEIGHT-1;
        //wall is 15 pixels, so objectoverlap should be false
        if((x <= x_distance) && x+SPRITE_WIDTH-1 >= allActors[i]->getX() && (y <= y_distance) && y+SPRITE_HEIGHT-1 >= allActors[i]->getY() && !allActors[i]->canBeMovedOnto()){
            return false;
        }
    }
    return true;
}

//x represents x value you want to goto, actor is this actor
bool StudentWorld::checkObjectOverlap(int x, int y, Actor* temp){
    int centerX = temp->getX() - x;
    int centerY = temp->getY() - y;
    int distance = sqrt(centerX*centerX + centerY*centerY);
    if(distance <= 10){
        return true;
    }
    return false;
}

void StudentWorld::setUpLevel(){
    Level lev(assetPath());
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
                        break;
                    }
                    case Level::dumb_zombie:{
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
