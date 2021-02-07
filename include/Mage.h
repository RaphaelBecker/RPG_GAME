#ifndef MAGE_H
#define MAGE_H

#include <string>

#include "Player.h"

using std::string;

class Mage : public Player //inherits from player
{

// Attributes --------------------------------------------------------
private:
    int stat_increase_boost = 5;
    static inline string currentCharacterType = "Mage"; // Indicates that the object is of class Mage

    // New attributes specific to Mage
    int _mana = 50;
    int _maxMana = 50;
    int _magic = 10;

public:
    Mage(int hp, string MageName, int ap, int dp, int maxhp, int playTime, int level);

    //Overloaded constructor to create Mage when loading as additional information regarding Mana magic and max mana is stored 
    Mage(int hp, string MageName, int ap, int dp, int maxhp, int playTime, int level, int mana, int maxMana, int magic);

    string getCharacterType() const;

    // Getters and setters for new attributes
    int getMana();

    void setMana(int mana);

    int getMaxMana();

    void setMaxMana(int maxMana);

    int getMagic();

    void setMagic(int magic);

    void fight(std::unique_ptr<Enemy> &enemy) override; // Fight function overrides the generic fight function implemented in player class

    void rest();

    void increaseStats() override;

    void printPlayerStatusScreen();

    void saveStateToFile(string filename);

};

#endif