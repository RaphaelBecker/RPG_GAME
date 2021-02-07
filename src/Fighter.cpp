
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <ctime>

#include "Fighter.h"
#include "Screen.h"
#include "Enemy.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

//Enemy class inherits from player class and extends it as most attributes are the same
Fighter::Fighter(int hp, string FighterName, int ap, int dp, int maxhp, int playTime, int level) : Player(hp, FighterName, ap, dp, maxhp, playTime)
{
    setLevel(level);
    cout << "#    Welcome Fighter " << FighterName << ". The first rule of Fight Club is: You do not talk about Fight Club. The second rule of Fight Club is: You do not talk about Fight Club." << endl;
}

string Fighter::getCharacterType() const
{
    return currentCharacterType;
}

void Fighter::increaseStats()
{
    setAp(getAp() + rand() % stat_increase_boost);
    setDp(getDp() + rand() % stat_increase_boost);
    setMax_hp(getMax_hp() + rand() % stat_increase_boost);
    cout << "Stats increased by " << stat_increase_boost;
}

void Fighter::fight(std::unique_ptr<Enemy> &enemy) // generates randon number and substracts from hp
{
    setPlayTime(getPlayTime() + 1);

    printHeaderScreen("FIGHT!");

    while (isAlive() && enemy->isAlive())
    {
        //Players move
        printHeaderScreen("Your Move... !");
        if (checkCriticalStrike())
        {
            printHeaderScreen("IT IS A CRITICAL HIT!");
            int damage_on_enemy = 1.5*getAp() - enemy->getDp(); // In critical strike the Attack points are multiplied by 1.5
            if (damage_on_enemy > 0)
            { //Damage cannot be <0
                cout << "#  You dealt " << damage_on_enemy << " damage" << endl;
                enemy->setHp(enemy->getHp() - damage_on_enemy);
            }
            else
            {
                cout << "#  It was not very effective! No damage. " << endl;
            }
        }
        else
        {
            int damage_on_enemy = getAp() - enemy->getDp();
            if (damage_on_enemy > 0)
            { //Damage cannot be <0
                cout << "#  You dealt " << damage_on_enemy << " damage" << endl;
                enemy->setHp(enemy->getHp() - damage_on_enemy);
            }
            else
            {
                cout << "#  It was not very effective! No damage. " << endl;
            }
        }
        singleSpacer();

        //Enemy's move
        printHeaderScreen(enemy->getName() + " Move... !");
        int damage_on_player = enemy->getAp() - getDp();
        if (damage_on_player > 0)
        { //Damage cannot be <0
            cout << "#  " << enemy->getName() << " dealt " << damage_on_player << " damage" << endl;
            setHp(getHp() - damage_on_player);
        }
        else
        {
            cout << "#  It was not very effective! No damage. " << endl;
        }

        singleSpacer();
        //Display remaining hit points
        cout << "#   Your Remaining HP is: " << getHp() << endl;
        cout << "#   " << enemy->getName() << "'s Remaining HP is: " << enemy->getHp() << endl;
    }

    if (isAlive()) //Checks if player is alive and if player is alive then the enemy has naturally fainted as one cannot exist while the other does. :(
    {
        levelUp();
        increaseStats();

        printHeaderScreen(enemy->getName() + " FAINTED");
    }
    else if (enemy->isAlive())
    {
        printHeaderScreen("YOU FAINTED. GAME OVER!");
    }
}

bool Fighter::checkCriticalStrike()
{
    // Checks if by pure luck a critical strike has been acheived. Returns true if it has
    srand (time(NULL));
    float rand_no = rand() % 100 + 1.0; 

    if (rand_no < critical_strike_chance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Printing all the players stats
void Fighter::printPlayerStatusScreen()
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
    cout << "#   Player Critical Strike Chance is: " << critical_strike_chance << endl;
    cout << "#   Player's Character Type is: " << currentCharacterType << endl;
}

// Saving the state of the player
void Fighter::saveStateToFile(string filename)
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