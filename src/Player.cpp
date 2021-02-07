#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <chrono> // For timing the fight function

//Including all local header files required.
#include "Player.h"
#include "Screen.h"
#include "Enemy.h"

using std::cin;
using std::cout;
using std::endl;

using std::string;

Player::Player(int hp, string name, int ap, int dp, int maxhp, int playTime) : hp(hp), name(name), ap(ap), dp(dp), max_hp(maxhp), playTime(playTime)
{
    singleSpacer();
    cout << "#   Player " << name << " has been created." << endl;
    cout << "#   With HP " << hp << "." << endl;
    cout << endl;
}

void Player::setHp(int x) //sets hp of the player
{
    hp = x;
}

int Player::getHp() const //returns hp of the player
{
    return hp;
}

void Player::setName(string y) //sets name of the player
{
    name = y;
}

string Player::getName() const //returns the name of the player
{
    return name;
}

void Player::setMax_hp(int mhp)
{
    max_hp = mhp;
}

int Player::getMax_hp() const
{
    return max_hp;
}

void Player::setAp(int a)
{
    ap = a;
}

int Player::getAp() const
{
    return ap;
}

void Player::setDp(int d)
{
    dp = d;
}

int Player::getDp() const
{
    return dp;
}

void Player::setPlayTime(int pt)
{
    playTime = pt;
}

int Player::getPlayTime() const
{
    return playTime;
}

void Player::levelUp()
{
    level++;
}

int Player::getLevel() const
{
    return level;
}

void Player::setLevel(int newLevel)
{
    level = newLevel;
}

void Player::rest()
{
    playTime++;
    hp = max_hp;
}
bool Player::isAlive() const
{
    return hp > 0;
}

void Player::fight(std::unique_ptr<Enemy> &enemy) // generates randon number and substracts from hp
{
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
    start = std::chrono::system_clock::now();

    playTime++;
    printHeaderScreen("FIGHT!");

    while (isAlive() && enemy->isAlive())
    {
        //Players move
        printHeaderScreen("Your Move... !");
        int damage_on_enemy = ap - enemy->getDp();
        if (damage_on_enemy > 0)
        { //Damage cannot be <0
            cout << "#  You dealt " << damage_on_enemy << " damage" << endl;
            enemy->setHp(enemy->getHp() - damage_on_enemy);
        }
        else
        {
            cout << "#  It was not very effective! No damage. " << endl;
        }
        singleSpacer();

        //Enemy's move
        printHeaderScreen(enemy->getName() + " Move... !");
        int damage_on_player = enemy->getAp() - dp;
        if (damage_on_player > 0)
        { //Damage cannot be <0
            cout << "#  " << enemy->getName() << " dealt " << damage_on_player << " damage" << endl;
            hp -= damage_on_player;
        }
        else
        {
            cout << "#  It was not very effective! No damage. " << endl;
        }

        singleSpacer();
        //Display remaining hit points
        cout << "#   Your Remaining HP is: " << hp << endl;
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
    
    end = std::chrono::system_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << " Fight Function Elapsed time: " << elapsed_time.count() << "ms" << std::endl;
}