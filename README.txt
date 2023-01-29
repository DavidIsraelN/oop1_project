# oop1_project
final project in oop course


// ------------------------------------------------------
# Written by: 
Mordechai Atiya. id - 208484576.
David Israel Naki. id - 204647168.

// ------------------------------------------------------
# About this program:

This program is the familiar old Pacman game, with all graphics.
It uses in SFML library for graphics, sounds and fonts.

// ------------------------------------------------------
# Files we created:

- ResourceManager.h - Singleton class:
                      Source class for all program data.
                      Loading the files of the program once - textures, audio, texts, fonts.
                      and receiving the data from anywhere in the program.

- Menu.h/cpp        - show the main menu before the game starts, and in the game when you press ESC.
                      The subclasses of this class are:
                        - Button.h/cpp      - Abstract class for all button types.
                        - NewGame.h/cpp     - Inherit class for New Game button.
                        - ChooseLevel.h     - Inherit class for Level Choose button.
                        - help.h/cpp        - Inherit class for Help button.
                        - ExitGame.h        - Inherit class for Exit Game button.
                        - Back.h            - Inherit class for Back button.
                        - Mute.h            - Inheritance class for the Mute button.

- Object.h/cpp      - Abstract class for all game Objects.
                      The subclasses of this class are:

                        - StaticObj.h  - Abstract class for Non-moving game objects.
                          it includes two kinds:
                             - Erasable.h  - Abstract class for Erasable game objects.
                                like: Cookie.h, Door.h, Key.h,
                                      Gift.h {include: FreezeGift.h, LifeGift.h, SuperPGift.h, TimeGift.h}.
                             - Wall.h - Inheritance class for the game object of Non-moving type - Wall

                        - MovingObj.h  - Abstract class for game objects that can move on the board (Moving).
                             - Pacman.h/cpp   - Inheritance class for Pacman
                             - Demon.h/cpp    - Inheritance class for Demon


- Controller.h/cpp  - Responsible for running the whole game.

- LevelManager.h/cpp- This class is responsible for selecting and running the levels, running the status bar,
                      moving the Objects, checking for collisions, changing level when the previous one is over,
                      and running the game over

- InfoBar.h/cpp      - Class for the game information bar.
                       Display the level number, life left, score, timer.

- LevelReader.h      - Class that is responsible for reading the correct file of the level,
                       and extracting the data from it.

- Level.h/cpp        - This class is responsible for the current level, displaying the level,
                       checking for collisions and responding, deleting eaten objects, etc..


// ------------------------------------------------------
# Main data structure:

The main data stored in some vectors of unique ptr.


// ------------------------------------------------------
# Noteworthy algorithm:

Demons run after the Pacman using an integrated algorithm: Random and nonrandom
Random: Choose a direction randomly, and more 3 directions in case the first is illegal.

Nonrandom: They get the general direction of Pacman and try to reduce the distance.
In case this is not possible, they can also go in another direction.

Usually, a demon will not return to the direction it came from, unless there is no other choice.


// ------------------------------------------------------
# bugs that we know:


// ------------------------------------------------------
# Notes -

* When demon is freeze, it behavior without changes.
* Supe pacman it Demons, and they return to their original position
* Gifts are chosen randomly when the level is created.
* There are two singleton classes. for resources and for sounds.
* There is the option to press on buttons in menu, by the keyboard keys
  (according to the first char - except in choosing level it by number).
* The dimensions of the window are the same in all the program.

* There is more, we didn't have enough time.