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
    return 1;
}

void StudentWorld::cleanUp()
{
}
StudentWorld::~StudentWorld(){
    cleanUp();
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
                        cout << "Location " << i << " " << j << " is empty" << endl;
                        break;
                    }
                    case Level::smart_zombie:{
                        cout << "Location 80,160 starts with a smart zombie" << endl;
                        break;
                    }
                    case Level::dumb_zombie:{
                        cout << "Location 80,160 starts with a dumb zombie" << endl;
                        break;
                    }
                    case Level::player:{
                        cout << "Location 80,160 is where Penelope starts" << endl;
                        example = new Penelope(i*16, j*16);
                        break;
                    }
                    case Level::exit:{
                        cout << "Location 80,160 is where an exit is" << endl;
                        break;
                    }
                    case Level::wall:{
                        cout << "Location 80,160 holds a Wall" << endl;
                        Wall* wall = new Wall(i*16, j*16);
                        allActors.push_back(wall);
                        break;
                    }
                    case Level::pit:{
                        cout << "Location 80,160 has a pit in the ground" << endl;
                        break;
                    }
                        // etc…
                }
            }
        }
    }
}
