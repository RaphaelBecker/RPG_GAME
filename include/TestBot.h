#ifndef TESTBOT_H
#define TESTBOT_H

#include <string>
#include <vector>
#include <time.h>

using std::string;

class TestBot
{

private:
    bool testMode;
    static inline unsigned bot_randomizer = 0;
public:
    TestBot(bool DesiredTestMode);

    void newGame(); //executes the New Game menu point without interaction with the user

    string getNextCommand(string menu[], int menuSize);

    bool getTestMode();

    void setTestMode(bool desiredTestMode);

    int random(int min, int max);
};

#endif