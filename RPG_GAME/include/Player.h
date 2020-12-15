#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
//#include "Enemy.h"

class Enemy;

using std::string;

class Player
{
    // Attributes --------------------------------------------------------
private:
    int hp;
    string name;
    // TODO: How sould these values be initialized?
    int max_hp;   // max healthpoints. Default value set in constructor
    int ap;       // attack points. Default value set in constructor
    int dp;       // defence points. Default value set in constructor
    int playTime; // When a player is instantiated, playTime is set to 0. Fight and rest take 1 day, else keeps day count

public:
    Player(int hp, string name, int ap, int dp, int max_hp, int playTime);

    // Getter and Setter -------------------------------------------------

    void setHp(int x); //sets hp of the player

    int getHp() const; //returns hp of the player

    void setName(string y); //sets name of the player

    string getName() const; //returns the name of the player

    void setMax_hp(int mhp); //sets max hp

    int getMax_hp()const; //gets max hp

    void setAp(int a); //sets attack points

    int getAp()const; //gets attack points

    void setDp(int d); //sets defence points

    int getDp() const; //gets defence points

    void setPlayTime(int pt); //sets play time

    int getPlayTime() const; //gets in game play time

    void rest(); //restores hp to max

    bool isAlive() const; //checks if you're alive.

    // Methods ------------------------------------------------------------
    void fight(std::unique_ptr<Enemy> &enemy); // generates randon number and substracts from hp
};

#endif
