
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <ctime>

#include "Enemy.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

//Enemy class inherits from player class and extends it as most attributes are the same
Enemy::Enemy(int hp, string enemyName, int ap, int dp, int maxhp, int playTime) : Player(hp, enemyName, ap, dp, maxhp, playTime)
{
    cout << "#    A Wild " << enemyName << " Appeared!" << endl;
}
