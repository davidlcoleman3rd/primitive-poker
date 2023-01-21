//***********************************************
//      DECK CLASS                              *
//                                              *
//***********************************************
//                                              *
//  This C++ class serves as a stack structure  *
//  of card objects.  This is the main source   *
//  card objects that players will draw from    *
//  when playing the game.                      *
//                                              *
//***********************************************
//                                              *
//  Version 0.1 pushed by David Coleman III on  *
//      01 - 18 - 23                            *
//                                              *
//  0.1 added Features:                         *
//  - Input function added - allows user to     *
//     use an integer as an argument for their  *
//     current test iteration                   *
//                                              *
//  - Print function added - allows user to     *
//     print the integer member variable that   *
//     stands for the current test iteration    *
//                                              *
//  - InputPrint function added - performs the  *
//     task of both Input and Print to save the *
//     client time and screen real estate       *
//                                              *
//***********************************************
//                                              *
//***********************************************
//                                              *
//  Version 0.1 pushed by David Coleman III on  *
//      01 - 18 - 23                            *
//***********************************************



//***********************************************

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <stack>

//***********************************************

const int DECK_SIZE = 52;       //The total number of cards in a deck

//***********************************************

class Deck {
public:
    Deck();             //Default constructor - Generates a new deck of cards

//******
    Deck(int/*in*/);    //Alternative constructor - Generates a deck made of X decks of cards (TO BE IMPLEMENTED LATER);

//******


private:
    stack<Card> stDeck;
};

#endif // DECK_H




