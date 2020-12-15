
#include <string>

using std::string;

//This is just to make the CLI interface look nicer with spaces and separaters
void singleSpacer();

void menuSpacer();

void printMenuScreen();

void printFightScreen(int pt);

void printHeaderScreen(string header);

void printPlayerStatusScreen(string name, int hp, int ap, int dp, int max_hp);
