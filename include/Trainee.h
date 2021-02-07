#ifndef TRAINEE_H
#define TRAINEE_H

#include <string>

#include "Player.h"

using std::string;

class Trainee : public Player //inherits from player
{

// Attributes --------------------------------------------------------
private:
    int stat_increase_boost = 3;
    static inline string currentCharacterType = "Trainee"; // Indicates that the object is of class Trainee

public:
    Trainee(int hp, string TraineeName, int ap, int dp, int maxhp, int playTime, int level);

    string getCharacterType() const;

    void increaseStats();

    void printPlayerStatusScreen();

    void saveStateToFile(string filename);

};

#endif