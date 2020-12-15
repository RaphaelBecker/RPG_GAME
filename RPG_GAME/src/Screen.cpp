//This is just to make the CLI interface look nicer with spaces and separaters
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <filesystem>


//Including local header file.
#include "Screen.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

using std::rand;
using std::time;

void singleSpacer()
{ //Just creates separation in the CLI
    cout << std::endl;
}
void menuSpacer()
{ //Just creates separation in the CLI
    cout << std::endl;
    cout << std::endl;
}

//Main menu
void printMenuScreen()
{
    menuSpacer();
    cout << "##########################################################" << endl;
    cout << "#   MENU:                                                #" << endl;
    cout << "##########################################################" << endl;
    cout << "#   New Game: Press [n]                                  #" << endl;
    cout << "#   Load Game: Press [l]                                 #" << endl;
    cout << "#   Exit: Press [e]                                      #" << endl;
    cout << "##########################################################" << endl;
}

//Fight club. I mean screen
void printFightScreen(int pt)
{
    menuSpacer();
    cout << "##########################################################" << endl;
    cout << "#   FIGHT: What would you like to do?                    #" << endl;
    cout << "##########################################################" << endl;
    cout << "#   Fight: Press [f]                                     #" << endl;
    cout << "#   Show Status: Press [d]                               #" << endl;
    cout << "#   Save: Press [s]                                      #" << endl;
    cout << "#   Rest: Press [r]                                      #" << endl;
    cout << "#   Exit: Press [e]                                      #" << endl;
    cout << "##########################################################\n";
    cout << "# Days passed: " << pt << endl; // Display playTime
}

//General print function
void printHeaderScreen(string header)
{
    menuSpacer();
    cout << "##########################################################" << endl;
    cout << "#  " << header << endl;
    cout << "##########################################################" << endl;
}

//Status report
void printPlayerStatusScreen(string name, int hp, int ap, int dp, int max_hp)
{
    printHeaderScreen("STATUS REPORT...");
    menuSpacer();
    cout << "#   Player Status Report: " << endl;
    cout << "#   Player Name is: " << name << endl;
    cout << "#   Player HP is: " << hp << endl;
    cout << "#   Player AP is: " << ap << endl;
    cout << "#   Player DP is: " << dp << endl;
    cout << "#   Player MAX_HP is: " << max_hp << endl;
}