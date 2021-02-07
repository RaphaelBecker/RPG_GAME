
#include <iostream>
#include <vector>
#include <cstdlib>

#include "TestBot.h"
#include "time.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

// TestBot class constructor
TestBot::TestBot(bool DesiredTestMode) : testMode(DesiredTestMode)
{
    cout << endl;
    cout << "### Testbot instantiated ###" << endl;
}

int TestBot::random(int min, int max) //range : [min, max]
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

// gets next input command
string TestBot::getNextCommand(string menu[], int menuSize)
{
    srand((unsigned int)time(NULL) + bot_randomizer); // To randomize bot selections
    bot_randomizer ++; // Increment randomizer to change seed time for next call
    //Just to check what choices our bot has    
    std::cout<<"Available options\n";
    for(int i=0; i<menuSize; i++)
    {
        cout << menu[i];
    }
    std::cout << " and rand was " << rand() << " with bot randomizer as " << bot_randomizer << std::endl;
    int a = 0;
    int random_selection;
    random_selection = rand()%menuSize;
    return menu[random_selection];
}

bool TestBot::getTestMode()
{
    return testMode;
}

void TestBot::setTestMode(bool desiredTestMode)
{
    testMode = desiredTestMode;
    cout << "#   testmode set!" << endl;
}
