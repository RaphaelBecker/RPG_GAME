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

//Including all local header files
#include "Player.h"
#include "Screen.h"
#include "Enemy.h"

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

string getUserInput(string screenMessageStringBugger)
{
    /* Ask user for unserinput and return userinput as string. screenMessageStringBugger will be printed on screen */
    string stringBuffer = "";
    singleSpacer();
    cout << screenMessageStringBugger << endl;
    while (getline(cin, stringBuffer)) //Cleaning the buffer before taking another input
        if (stringBuffer != "")
            break;

    return stringBuffer;
}

bool IsPathExist(const std::string &s)
{
    struct stat buffer;
    return (stat(s.c_str(), &buffer) == 0);
}

void saveGame(string filename, unique_ptr<Player> &user)
{

    if (IsPathExist("../save"))
    {
        //Check if saved file already exists
        char overwrite = ' ';
        ifstream f(filename.c_str());
        if (f.good())
        {
            printHeaderScreen("File Already Exists. Do You Want To Overwrite? Press [y] to continue and [n] to go back");
            cin >> overwrite;

            if (overwrite == 'y') //If overwrite is selected
            {
                // Save file
                printHeaderScreen("SAVING GAME...");
                std::ofstream myfile;
                myfile.open(filename);
                myfile << user->getHp() << "," << user->getName() << "," << user->getAp() << "," << user->getDp() << "," << user->getMax_hp() << "," << user->getPlayTime() << std::endl;
                myfile.close();
                printHeaderScreen("File Saved");
                return;
            }

            else if (overwrite == 'n') //If not overwrite is selected
            {
                printHeaderScreen("File Not Saved!");
                return;
            }
            else
            {
                cout << "Incorrect command. Please try again \n";
                saveGame(filename, user);
            }
        }
        else
        {
            printHeaderScreen("SAVING GAME...");
            std::ofstream myfile;
            myfile.open(filename);
            myfile << user->getHp() << "," << user->getName() << "," << user->getAp() << "," << user->getDp() << "," << user->getMax_hp() << "," << user->getPlayTime() << std::endl;
            myfile.close();
            printHeaderScreen("File Saved");
            return;
        }

        return;
    }
    else
    {
        fs::create_directory("../save");

        //Check if saved file already exists
        char overwrite = ' ';
        ifstream f(filename.c_str());
        if (f.good())
        {
            printHeaderScreen("File Already Exists. Do You Want To Overwrite? Press [y] to continue and [n] to go back");
            cin >> overwrite;

            if (overwrite == 'y') //If overwrite is selected
            {
                // Save file
                printHeaderScreen("SAVING GAME...");
                std::ofstream myfile;
                myfile.open(filename);
                myfile << user->getHp() << "," << user->getName() << "," << user->getAp() << "," << user->getDp() << "," << user->getMax_hp() << "," << user->getPlayTime() << std::endl;
                myfile.close();
                printHeaderScreen("File Saved");
                return;
            }

            else if (overwrite == 'n') //If not overwrite is selected
            {
                printHeaderScreen("File Not Saved!");
                return;
            }
            else
            {
                cout << "Incorrect command. Please try again \n";
                saveGame(filename, user);
            }
        }
        else
        {
            printHeaderScreen("SAVING GAME...");
            std::ofstream myfile;
            myfile.open(filename);
            myfile << user->getHp() << "," << user->getName() << "," << user->getAp() << "," << user->getDp() << "," << user->getMax_hp() << "," << user->getPlayTime() << std::endl;
            myfile.close();
            printHeaderScreen("File Saved");
            return;
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
    string loadData[6];

    ifstream myfile;
    myfile.open(filename);
    int i = 0;
    // gets string token from myfile separated by ',' and saves them into loadData Array
    while (myfile.good())
    {
        string line;
        std::getline(myfile, line, ',');
        loadData[i] = line;
        i++;
    }
    // Instantiate new Player Object with name and healthpoints
    hp = std::stoi(loadData[0]);
    name = loadData[1];
    ap = std::stoi(loadData[2]);
    dp = std::stoi(loadData[3]);
    maxhp = std::stoi(loadData[4]);
    playTime = std::stoi(loadData[5]);
    //Instantiate a new player on the heap with parameters from the saved file:
    unique_ptr<Player>
        user = make_unique<Player>(hp, name, ap, dp, maxhp, playTime);
    return user;
}

void game_loop(unique_ptr<Player> &user);

int main()
{
    /* attribute section */
    string menu[3] = {"n", "l", "e"};
    string inputBuffer;
    string nameBuffer;

    /* print main menu */
    printMenuScreen();
    /* Ask user for user input. User has to choose menu point */
    inputBuffer = getUserInput("#   Your Choice: ");

    /* User wants to start a new game. 
    New user will be instantiated with name and healthpoints (hp) = 100 */
    if (inputBuffer == menu[0])
    {
        // Execute command according to identifier
        printHeaderScreen("NEW GAME!");
        nameBuffer = getUserInput("#   Please enter name: ");
        int hp = 100;

        //Instantiate a new player on the heap:
        unique_ptr<Player> myPlayer = make_unique<Player>(hp, nameBuffer, 3, 3, hp, 0);
        //Player created with default attack points and defence points, passed time is 0;
        //start game loop
        game_loop(myPlayer);
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
            game_loop(myPlayer);
        }
    }

    /* User wants to exit game. Game will be exit and user will be notified */
    else if (inputBuffer == menu[2])
    {
        cout << "Exit game. Goodbye!" << endl;
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

//GAME LOOP.
//this is the main engine of the game

void game_loop(unique_ptr<Player> &user)
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
    while (runLoop)
    {
        printFightScreen(user->getPlayTime());
        stringBufferChoice = getUserInput("#   Your Choice: ");

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
        }
        else if (stringBufferChoice == choices[1]) //Print stats
        {
            printPlayerStatusScreen(user->getName(), user->getHp(), user->getAp(), user->getDp(), user->getMax_hp());
        }
        else if (stringBufferChoice == choices[2])
        {
            string saveFileName = "../save/SavedFile.csv";
            saveGame(saveFileName, user);
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
