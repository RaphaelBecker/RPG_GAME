# AP_project_RPG_game

Created by: Waleedbinkhalid74 and me.
The project is implemented as an assignment in the Advanced Programming Course WS 2020/2021 at the Technical University of Munich TUM.
Currently at sprint 2 from 3 sprints.
## How to use

1. Use the Makefile to compile: `make`
2. Use make .PHONY to clean the project (delete .o files in ..src/obj)
3. Run executalbe with: `./rpg_game` which is stored in the build folder

## Game Description

Description..

## Gameplay

Description..

## Special Characteristics

The game is terminal based. 

## Screenshots

| Grid |
| ---- |
| ...  |

## Key Bindings

| Action      | Key  |
| ----------- | ---- |
| New Game    | n    |
| Load Game   | l    |
| Fight       | f    |
| Show Status | d    |
| Save        | s    |
| exit        | e    |
| Rest        | r    |


Changelog
=========

v2
--

* moved the source to src/ and saves to saves/
* Encapsulated the Engine in a class
* Introduced a Rest mechanic in the main game loop to restore HP
* Introduced a day counter (int) in the Engine to count how many in game day passed (fight and rest increase the day counter)
* Introduced BaseClass for the game characters, refactored the player to use be an instance of this class (using unique_ptr)
* Introduced CharacterFactory namespace and functions to create characters and serialize/deserialize them
* Modified the save/load function to save/load the engine state (dayCounter and player, using the CharacterFactory)
* Introduced enemy class which inherits from the player class.


Features
========

Main menu
---------

* New Game: start a game, initialize a player (ask for name) and present the main game loop
* Load Game: load player stats from a save file and present the main game loop
* Exit: terminate the program


Main Game loop
--------------

As long as the player is alive, the following options are given:

* Fight: fight against an enemy (dummy goblin all the time), takes a day
* Rest: fully heal the player, takes a day
* Show stats: display the current player's stats
* Save: save the game state to a given save file (see save/load feature)
* Rest: Restores Health Points to max 
* Exit: terminate the program


Character Stats
---------------

A character can be the player or an enemy.

Stored in a BaseClass Object.

* Name: name of the character
* Type: name of the current class
* HP: current HP
* Max HP: maximum HP, resting set HP to this value
* Attack: attack stat for fighting
* Defense: defense stat for fighting
* Days passed: The number of in game days. Fight and Rest take 1 day the remaining functions to not change the time

A character is alive as long as HP > 0.

Fights
------

Two chacters fight as long as both are alive.

Each deals attacker.atk - defender.def damages (min 0) to the other at the same time.
Repeat until one dies.


Save/Load feature
-----------------

Data are saved in clear text (here csv format).
It uses the CharacterFactory to serialize/deserialize a player character.

* Saving: ask the player for the save file name and store the game state in it. Override existing save if already existing.
* Loading: ask the player for a save file name and load it.


Old Changelog
=============

v1
--

* v1 of the game features
* Makefile: `make` to build the application (by default `miniRPG`), `make clean` to clean



**Enjoy! :D**


