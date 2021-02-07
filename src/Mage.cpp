
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <ctime>

#include "Mage.h"
#include "Screen.h"
#include "Enemy.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;

//Mage class inherits from player class and extends it as most attributes are the same
Mage::Mage(int hp, string MageName, int ap, int dp, int maxhp, int playTime, int level) : Player(hp, MageName, ap, dp, maxhp, playTime)
{
    setLevel(level);
    cout << "#    Mage " << MageName << ", The Council of Wizards welcome you." << endl;
}

Mage::Mage(int hp, string MageName, int ap, int dp, int maxhp, int playTime, int level, int mana, int maxMana, int magic) : Player(hp, MageName, ap, dp, maxhp, playTime)
{
    setLevel(level);
    setMana(mana);
    setMaxMana(maxMana);
    setMagic(magic);
    cout << "#    Mage " << MageName << ", The Council of Wizards welcome you." << endl;
}

string Mage::getCharacterType() const
{
    return currentCharacterType;
}

int Mage::getMana()
{
    return _mana;
}

void Mage::setMana(int mana)
{
    _mana = mana;
}

int Mage::getMaxMana()
{
    return _maxMana;
}

void Mage::setMaxMana(int maxMana)
{
    _mana = maxMana;
}

int Mage::getMagic()
{
    return _magic;
}

void Mage::setMagic(int magic)
{
    _magic = magic;
}

void Mage::fight(std::unique_ptr<Enemy> &enemy) // generates randon number and substracts from hp
{
    setPlayTime(getPlayTime() + 1);

    printHeaderScreen("FIGHT!");

    while (isAlive() && enemy->isAlive())
    {
        //Players move
        printHeaderScreen("Your Move... !");
        if (getMana() >= 5) 
        {
        // If enough mana is available spend some to attack using a magical spell that uses my magic stat instead of
        //attack stat to inflict damage. Otherwise attack using my attack stat. Resting restores
        //mana to full.
            printHeaderScreen("AVADA KEDAVRA!");
            setMana(getMana()-5); // consumed 5 mana points
            int damage_on_enemy = getMagic() - enemy->getDp();
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

void Mage::rest()
{
    // Also restores mana
    setPlayTime(getPlayTime() + 1);
    setHp(getMax_hp());
    setMana(getMaxMana());    
}

void Mage::increaseStats()
{
    setAp(getAp() + rand() % stat_increase_boost);
    setDp(getDp() + rand() % stat_increase_boost);
    setMax_hp(getMax_hp() + rand() % stat_increase_boost);
    setMaxMana(getMaxMana() + rand() % stat_increase_boost);
    setMagic(getMagic() + rand() % (stat_increase_boost + 2)); // On level up, magic stat increases faster than attack stat.

}

void Mage::printPlayerStatusScreen()
{
    // Extra attributes also displayed
    printHeaderScreen("STATUS REPORT...");
    menuSpacer();
    cout << "#   Player Status Report: " << endl;
    cout << "#   Player Name is: " << getName() << endl;
    cout << "#   Player HP is: " << getHp() << endl;
    cout << "#   Player AP is: " << getAp() << endl;
    cout << "#   Player DP is: " << getDp() << endl;
    cout << "#   Player MAX_HP is: " << getMax_hp() << endl;
    cout << "#   Player Level is: " << getLevel() << endl;
    cout << "#   Player Mana is: " << getMana() << endl;
    cout << "#   Player Max Mana is: " << getMaxMana() << endl;
    cout << "#   Player Magic is: " << getMagic() << endl;
    cout << "#   Player's Character Type is: " << currentCharacterType << endl;
}

// Saving the state of the player
void Mage::saveStateToFile(string filename)
{
    printHeaderScreen("SAVING GAME...");
    std::ofstream myfile;
    myfile.open(filename);
    // More data to save for Mage class. Rest are generic
    myfile << getHp() << "," << getName() << "," << getAp() << "," << getDp() << "," << getMax_hp() << "," << getPlayTime() << "," << getLevel() << "," << getCharacterType() << "," << getMana() <<"," << getMaxMana() <<"," << getMagic() << std::endl;
    myfile.close();
    printHeaderScreen("File Saved");
    return;
}