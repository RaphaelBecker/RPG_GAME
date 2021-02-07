
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <ctime>

#include "Trainee.h"
#include "Screen.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

//Enemy class inherits from player class and extends it as most attributes are the same
Trainee::Trainee(int hp, string TraineeName, int ap, int dp, int maxhp, int playTime, int level) : Player(hp, TraineeName, ap, dp, maxhp, playTime)
{
    setLevel(level);
    cout << "#    Padawan " << TraineeName << ", The Jedi Council welcomes you." << endl;
}

string Trainee::getCharacterType() const
{
    return currentCharacterType;
}

void Trainee::increaseStats()
{
    setAp(getAp() + rand()%stat_increase_boost);
    setDp(getDp()+ rand()%stat_increase_boost);
    setMax_hp(getMax_hp() + rand()%stat_increase_boost);
    cout<<"Stats increased by " << stat_increase_boost;
}

void Trainee::printPlayerStatusScreen()
{
    printHeaderScreen("STATUS REPORT...");
    menuSpacer();
    cout << "#   Player Status Report: " << endl;
    cout << "#   Player Name is: " << getName() << endl;
    cout << "#   Player HP is: " << getHp() << endl;
    cout << "#   Player AP is: " << getAp() << endl;
    cout << "#   Player DP is: " << getDp() << endl;
    cout << "#   Player MAX_HP is: " << getMax_hp() << endl;
    cout << "#   Player Level is: " << getLevel() << endl;
    cout << "#   Player's Character Type is: " << currentCharacterType << endl;
}

// Saving the state of the player
void Trainee::saveStateToFile(string filename)
{
    printHeaderScreen("SAVING GAME...");
    std::ofstream myfile;
    myfile.open(filename);
    // More data to save for Mage class. Rest are generic
    myfile << getHp() << "," << getName() << "," << getAp() << "," << getDp() << "," << getMax_hp() << "," << getPlayTime() << "," << getLevel() << "," << getCharacterType() << std::endl;
    myfile.close();
    printHeaderScreen("File Saved");
    return;
}