// This project is created by Waleed and Raphael

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <filesystem> //for load save
#include <memory>     // For using unique pointers
#include <sys/stat.h>
#include <vector>

//Including all local header files
#include "Player.h"
#include "Screen.h"
#include "Enemy.h"
#include "Trainee.h"
#include "Mage.h"
#include "Fighter.h"
#include "TestBot.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::make_unique;
using std::ofstream;
using std::rand;
using std::string;
using std::time;
using std::unique_ptr;

namespace fs = std::filesystem;

string getUserInput(string screenMessageStringBugger, unique_ptr<TestBot> &testBot, string menu[], int menuSize, bool inputRequired)
{

    string stringBuffer = "";
    // If testbot is false, interaction with user is required
    if (testBot->getTestMode() == false)
    {
        cout << "#   Playmode!" << endl;
        /* Ask user for unserinput and return userinput as string. screenMessageStringBugger will be printed on screen */
        singleSpacer();
        cout << screenMessageStringBugger << endl;
        while (getline(cin, stringBuffer)) //Cleaning the buffer before taking another input
            if (stringBuffer != "")
                break;
    }
    // if testbot is set to true, commands will be executed from command vector 'inputSequence'
    else if (testBot->getTestMode() == true)
    {
        // If programm asks for user name, "dummyName" will be passed
        if (inputRequired == true)
        {
            stringBuffer = "dummyName";
            cout << "TestBot has set 'dummyName' as Player name" << endl;
        }
        // If input from menu is required, possible input commands are passed to TestBot. A random choice will be returned by getNextCommand(menu)
        else
        {
            stringBuffer = testBot->getNextCommand(menu, menuSize);
            cout << "#   Testmode! Next random command: " << stringBuffer << endl;
        }
    }
    return stringBuffer;
}

bool IsPathExist(const std::string &s)
{
    struct stat buffer;
    return (stat(s.c_str(), &buffer) == 0);
}

void saveFile(string filename, unique_ptr<Player> &user)
{
    // Runtime polymorphism to save the state of the player according to its current class
    user->saveStateToFile(filename);
}

void saveGame(string filename, unique_ptr<Player> &user, unique_ptr<TestBot> &testBot)
{
    string menuSave[2] = {"y", "n"};
    string overwrite = " ";

    if (IsPathExist("../save"))
    {
        //Check if saved file already exists
        ifstream f(filename.c_str());

        if (f.good())
        {
            printHeaderScreen("File Already Exists. Do You Want To Overwrite? Press [y] to continue and [n] to go back");
            overwrite = getUserInput("#   Your Choice: ", testBot, menuSave, 2, false);

            if (overwrite == "y") //If overwrite is selected
            {
                // Save file
                saveFile(filename, user);
            }

            else if (overwrite == "n") //If not overwrite is selected
            {
                printHeaderScreen("File Not Saved!");
                return;
            }
            else
            {
                cout << "Incorrect command. Please try again \n";
                saveGame(filename, user, testBot);
            }
        }
        else
        {
            saveFile(filename, user);
        }

        return;
    }
    else
    {
        fs::create_directory("../save");

        //Check if saved file already exists
        ifstream f(filename.c_str());
        if (f.good())
        {
            printHeaderScreen("File Already Exists. Do You Want To Overwrite? Press [y] to continue and [n] to go back");
            overwrite = getUserInput("#   Your Choice: ", testBot, menuSave, 2, false);

            if (overwrite == "y") //If overwrite is selected
            {
                // Save file
                saveFile(filename, user);
            }

            else if (overwrite == "n") //If not overwrite is selected
            {
                printHeaderScreen("File Not Saved!");
                return;
            }
            else
            {
                cout << "Incorrect command. Please try again \n";
                saveGame(filename, user, testBot);
            }
        }
        else
        {
            saveFile(filename, user);
        }

        return;
    }
}

unique_ptr<Player> loadGame(string filename)
{ /* returns a new Player Instance with game data from filename */
    int hp;
    string name;
    int ap = 0;
    int dp = 0;
    int maxhp = 0;
    int playTime = 0;
    int level = 0;
    string characterType;
    std::vector<std::string> loadData;

    ifstream myfile;
    myfile.open(filename);
    // gets string token from myfile separated by ',' and saves them into loadData Array
    while (myfile.good())
    {
        string line;
        std::getline(myfile, line, ',');
        loadData.push_back(line);
    }

    // Instantiate new Player Object with name and healthpoints
    hp = std::stoi(loadData.at(0));
    name = loadData.at(1);
    ap = std::stoi(loadData.at(2));
    dp = std::stoi(loadData.at(3));
    maxhp = std::stoi(loadData.at(4));
    playTime = std::stoi(loadData.at(5));
    level = std::stoi(loadData.at(6));
    characterType = loadData.at(7);

    //Instantiate a new player on the heap with parameters from the saved file:
    if (characterType == "Mage")
    {
        // Need to extract mana, max mana and magic info if the saved player is of class Mage
        int mana = std::stoi(loadData.at(8));
        int maxMana = std::stoi(loadData.at(9));
        int magic = std::stoi(loadData.at(10));
        return std::make_unique<Mage>(hp, name, ap, dp, maxhp, playTime, level, mana, maxMana, magic);
    }
    else if (characterType == "Fighter\n")
    {
        return std::make_unique<Fighter>(hp, name, ap, dp, maxhp, playTime, level);
    }
    else if (characterType == "Trainee\n")
    {
        return std::make_unique<Trainee>(hp, name, ap, dp, maxhp, playTime, level);
    }
    else
    {
        cout << "SOMETHING WENT WRONG!";
        return NULL;
    }
}

void game_loop(unique_ptr<Player> &user, unique_ptr<TestBot> &testBot);

int main()
{

    /* attribute section */
    string menu[4] = {"n", "l", "e", "b"};
    size_t menuSize = 4;
    string inputBuffer;
    string nameBuffer;

    //Instantiate a new testbot on the heap with testmode = false per default. Will be set to true, if 'b' is pressed in main menu
    unique_ptr<TestBot> testBot = make_unique<TestBot>(false);

    /* print main menu */
    printMenuScreen();
    /* Ask user for user input. User has to choose menu point */
    inputBuffer = getUserInput("#   Your Choice: ", testBot, menu, menuSize, false);

    /* User wants to start a new game. 
    New user will be instantiated with name and healthpoints (hp) = 100 */
    if (inputBuffer == menu[0])
    {
        // Execute command according to identifier
        printHeaderScreen("NEW GAME!");
        nameBuffer = getUserInput("#   Please enter name: ", testBot, menu, menuSize, true);
        int hp = 100;

        //Instantiate a new player on the heap:
        unique_ptr<Player> myPlayer = make_unique<Trainee>(hp, nameBuffer, 3, 3, hp, 0, 0);
        //Player created with default attack points and defence points, passed time is 0;
        //start game loop
        game_loop(myPlayer, testBot);
    }

    /* User wants to load game. A new Player Object will be initialized with data from SavedFile.csv. (I. e. name, health points) 
    If SavedFile.csv does not exist, notify user and exit game. */
    else if (inputBuffer == menu[1])
    {
        printHeaderScreen("LOADING GAME...");
        if (!ifstream("../save/SavedFile.csv"))
        {
            cout << "Saved File does not exist..." << endl;
            main();
        }
        else
        {
            //Instantiate new player based on previous saved state on the heap
            unique_ptr<Player> myPlayer = loadGame("../save/SavedFile.csv");
            game_loop(myPlayer, testBot);
        }
    }

    /* User wants to exit game. Game will be exit and user will be notified */
    else if (inputBuffer == menu[2])
    {
        cout << "Exit game. Goodbye!" << endl;
        return EXIT_SUCCESS;
    }

    // User wants to test the app via bot:
    else if (inputBuffer == menu[3])
    {
        cout << "#   Bot plays the game!" << endl;
        unique_ptr<Player> dummy = make_unique<Trainee>(100, "dummy", 3, 3, 100, 0, 0);

        // set game to testmode
        testBot->setTestMode(true);

        // play game in testmode
        game_loop(dummy, testBot);

        return EXIT_SUCCESS;
    }

    /* User input does not match to menu. User will be notified, game will exit */
    else
    {
        cout << "Input does not match to menu. Type <Exit> to exit game!" << endl;
        main();
    }

    return 0;
}

std::unique_ptr<Player> Evolve(string choice, const unique_ptr<Player> &user, unique_ptr<TestBot> &testBot)
{
    // is passed to testBot for randomized input
    string menuEvolve[2] = {"m", "f"};
    size_t menuEvoleSize = 2;
    if (choice == "m")
    { //int hp, string TraineeName, int ap, int dp, int maxhp, int playTime
        cout << "Mage\n";
        return std::make_unique<Mage>(user->getHp(), user->getName(), user->getAp(), user->getDp(), user->getMax_hp(), user->getPlayTime(), user->getLevel());
    }
    else if (choice == "f")
    {
        cout << "Fighter\n";
        return std::make_unique<Fighter>(user->getHp(), user->getName(), user->getAp(), user->getDp(), user->getMax_hp(), user->getPlayTime(), user->getLevel());
    }
    else
    {
        cout << "This evolution does not exist. Please select again. \n";
        string levelUpChoice = getUserInput("#   Your Choice: ", testBot, menuEvolve, menuEvoleSize, false);
        return Evolve(levelUpChoice, user, testBot);
    }
}

//GAME LOOP.
//this is the main engine of the game

void game_loop(unique_ptr<Player> &user, unique_ptr<TestBot> &testBot)
{
    /* Prints Fight Screen with 4 menu coices: "Fight", "Show Status", "Save", "Exit"
# Fight:        New hp is calculated. If hp < 0, Game over, game wil be exit
# Show Status:  Prints Player stat. I. e. name, health points
# Save:         Saves Player stats i.e name and hp to csv file
# Exit:         Exit game without saving
*/
    bool runLoop = true;
    string stringBufferChoice;
    string choices[5] = {"f", "d", "s", "e", "r"};
    size_t fightScreenSize = 5;

    while (runLoop)
    {
        printFightScreen(user->getPlayTime());
        stringBufferChoice = getUserInput("#   Your Choice: ", testBot, choices, fightScreenSize, false);

        if (stringBufferChoice == choices[0]) //Fight Club. Shh...
        {
            singleSpacer();
            // TODO:
            //Creating new Enemy on the heap
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(20, "Pikachu", 4, 2, 20, 0); //Gotta catch em all :D
            //Enemy created with default attack points and defence points
            cout
                << "#   Fight! \n";
            user->fight(enemy);
            if (user->getHp() <= 0)
            {
                singleSpacer();
                cout << "##########################################################" << endl;
                cout << "#   YOU DIED. Hidetaka Miyazaki sends his regards :(     #" << endl;
                cout << "##########################################################" << endl;

                main();
                runLoop = false;
            }
            else if (user->isAlive() && user->getLevel() == 10)
            {
                string menuEvolve[2] = {"m", "f"};
                size_t menuEvolveSize = 2;
                printHeaderScreen("Oh Look. You are evolving.... What Would You Like Evolve Into?");
                cout << "#   Mage: Press [m]                                     #" << endl;
                cout << "#   Fighter: Press [f]                                  #" << endl;
                string levelUpChoice = getUserInput("#   Your Choice: ", testBot, menuEvolve, menuEvolveSize, false);
                user = Evolve(levelUpChoice, user, testBot);
            }
        }
        else if (stringBufferChoice == choices[1]) //Print stats
        {
            user->printPlayerStatusScreen();
        }
        else if (stringBufferChoice == choices[2])
        {
            string saveFileName = "../save/SavedFile.csv";
            saveGame(saveFileName, user, testBot);
            singleSpacer();
        }
        else if (stringBufferChoice == choices[3]) //Exit Game
        {
            singleSpacer();
            cout << "#   Exiting Game ... " << endl;
            runLoop = false;
        }
        else if (stringBufferChoice == choices[4]) //Restoring HP
        {
            singleSpacer();
            cout << "You used a Hyperpotion... Restoring hp to max... " << endl;
            user->rest(); //Restores HP to max HP which was set as original HP
        }
        else
        {
            singleSpacer();
            cout << "#   Incorrect Entry. Please try again" << endl;
        }
    }
}
