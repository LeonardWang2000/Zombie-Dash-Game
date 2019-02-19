#include "StudentWorld.h"
#include "GameConstants.h"
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
                delete player;
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
    vector<Actor>::iterator it;
    for(int i = 0; i < allActors.size(); i++){
        cout << "Actor position: " << x << "Wall pos: " << allActors[i]->getX() << endl;
        if(allActors[i]->getY() == y && allActors[i]->getX() == x){
            return false;
        }
    }
    return true;
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
                        player = new Penelope(i*16, j*16, this);
                        break;
                    }
                    case Level::exit:{
                        break;
                    }
                    case Level::wall:{
                        Wall* wall = new Wall(i*16, j*16, this);
                        allActors.push_back(wall);
                        break;
                    }
                    case Level::pit:{
                        break;
                    }
                        // etc…
                }
            }
        }
    }
}
