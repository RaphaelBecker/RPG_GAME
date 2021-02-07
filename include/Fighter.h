#ifndef FIGHTER_H
#define FIGHTER_H

#include <string>

#include "Player.h"

using std::string;

class Fighter : public Player //inherits from player
{

// Attributes --------------------------------------------------------
private:
    int stat_increase_boost = 5;
    float critical_strike_chance = 25.0;
    static inline string currentCharacterType = "Fighter"; // Indicates that the object is of class Fighter

public:
    Fighter(int hp, string FighterName, int ap, int dp, int maxhp, int playTime, int level);

    string getCharacterType() const;

    void increaseStats() override;

    void fight(std::unique_ptr<Enemy> &enemy) override; // Fight function overrides the generic fight function implemented in player class

    bool checkCriticalStrike();

    void printPlayerStatusScreen();

    void saveStateToFile(string filename);
};

#endif