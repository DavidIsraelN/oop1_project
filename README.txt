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

- Controller.cpp    - Responsible for running the whole game.

- Object.h/cpp      - Abstract class for all game Objects.
                      The subclasses of this class are:
                        - StaticObj.h  - Abstract class for Non-moving game objects.
                            it includes two kinds:
                                - Erasable.h  - Abstract class for Erasable game objects.
                                  like: Cookie.h, Door.h, Gift.h, 
                        - MovingObj.h  - Abstract class for game objects that can move on the board (Moving).
-

                           The subclasses of this class are:
                             - Erasable.h  - Abstract class for Erasable game objects.
                               The subclasses of this class are:
                                 - Cookie.h
                                 - Door.h
                                    -


- Board.cpp -       Implementation of the Board class.
                    Takes the board from "Board.txt" to a main vector that stores the board.
                    Displays the board and updates it with each action.

- io.cpp -          Implementation of the io class.
                    Helps in receiving direction input from the user for the Pacman.

- Location.cpp -    Implementation of the Location struct.
                    Stores the position of the row and column in it.
                    Can compare two locations.

- Pacman.cpp -      Implementation of the Pacman class.
                    Set the Pacman's direction from the user, and checks that the input is correct.
                    In addition, checks the collisions and updates the Pacman's score and life.

- Spacman.cpp -     Implementation of the Spacman class.
                    Changes Pacman's features, so it doesn't get eaten by the Demons.

- Demon.h -         Header file for Demon class.
- Demon.cpp -       Implementation of the Demon class.
                    Sends the Demons to chase Pacman.

- Immobile.h -      Header file for Immobile class.
- Immobile.cpp -    Implementation of the Immobile class.
                    Designed to store in a vector the objects that do not move,
                    like: cookies, doors, keys and gifts.

// ------------------------------------------------------
# Main data structure:

The main data stored in a string vector, in the Board class.

// ------------------------------------------------------
# Noteworthy algorithm:

Demons run after the Pacman using an integrated algorithm: Random and nonrandom
Random: Choose a direction randomly, and more 3 directions in case the first is illegal.

Nonrandom: They get the general direction of Pacman and try to reduce the distance.
In case this is not possible, they can also go in another direction.

Usually, a demon will not return to the direction it came from, unless there is no other choice.

// ------------------------------------------------------
# bugs that we know:

1:  Sometimes when one demon get-over another demon, it raises it
    (We try to fix it, but it's still not working always well).

2:  When there is pass in the board from side to side, demons not always go through it.

// ------------------------------------------------------
# Notes -

