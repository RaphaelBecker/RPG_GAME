#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "Player.h"

using std::string;

class Enemy : public Player //inherits from player
{
public:
    Enemy(int hp, string enemyName, int ap, int dp, int maxhp, int playTime);
};

#endif