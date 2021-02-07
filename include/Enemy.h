#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "Player.h"

using std::string;

class Enemy : public Player //inherits from player
{
private:
    static inline string currentCharacterType = "Trainee"; // Indicates that the object is of class Trainee

public:
    Enemy(int hp, string enemyName, int ap, int dp, int maxhp, int playTime);

    string getCharacterType() const;

    void increaseStats();

    void printPlayerStatusScreen();

    void saveStateToFile(string filename);
};

#endif