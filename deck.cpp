
//***********************************************
//      DECK CLASS IMPLEMENTATION               *
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

#include "deck.h"

//***********************************************

//const int DECK_SIZE = 52;       //The total number of cards in a deck

//***********************************************

    Deck::Deck() {
        Card* tempPtr;
        for (int iIterSuit = 0; iIterSuit < MAX_SUITS; iIterSuit++) {
            for (int iIterRank = 0; iIterRank < MAX_RANKS; iIterRank++) {
                tempPtr = new Card(iIterSuit, iIterRank);
                stDeck.push(*(tempPtr));
            }
        }
    }

//******
    Deck::Deck(int/*in*/) {                         //Alternative constructor - Generates a deck made of X decks of cards (TO BE IMPLEMENTED LATER);

    }

//******
    void Deck::Shuffle(int iInput/*in*/) {          //Shuffles the deck x times, where x is the argument passed to the function

    }

//******
    Card Deck::DealCard(int iInState/*in*/){        //Peeks a card from the top of the deck and distributes it to a player, popping it from deck
        Card cTemp(stDeck.top());
        stDeck.pop();
        cTemp.SetState(CardState(iInState));
        return cTemp;
    }

//******
    Deck::~Deck(){                                  //Destructor, currently does nothing

    }

/*
private:
    stack<Card> stDeck;
};
*/
