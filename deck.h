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
//  Version 0.0.1 pushed by David Coleman III on*
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




