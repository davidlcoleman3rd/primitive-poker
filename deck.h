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
//  Version 0.0.4.1 pushed by David Coleman III *
//  on  01 - 24 - 23                            *
//***********************************************



//***********************************************

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <stack>

//***********************************************

const int MAX_SUITS = 4;                        //The total number of suits in a deck
const int MAX_RANKS = 13;                       //The total number of number values in a deck
const int DECK_SIZE = MAX_SUITS + MAX_RANKS;    //The total number of cards in a deck

//***********************************************

class Deck {
public:
    Deck();             //Default constructor - Generates a new deck of cards

//******
    Deck(int/*in*/);    //Alternative constructor - Generates a deck made of X decks of cards (TO BE IMPLEMENTED LATER);

//******
    void Shuffle();     //Shuffles the deck

//******
    Card DealCard();    //Peeks a card from the top of the deck and distributes it to a player

//******
    ~Deck();            //Destructor - currently does nothing


private:
    std::stack<Card> stDeck;
};

#endif // DECK_H




