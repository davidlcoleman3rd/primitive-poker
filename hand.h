//***********************************************
//      HAND CLASS                              *
//                                              *
//***********************************************
//                                              *
//  This C++ class serves as a vector structure *
//  of card objects.  This is the main source   *
//  card objects that players will use as       *
//  their "hands" when playing the game.        *
//                                              *
//***********************************************
//  Version 0.0.4.1 pushed by David Coleman III *
//  on  01 - 24 - 23                            *
//***********************************************

#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "deck.h"
#include <vector>

//***********************************************

const int HAND_STATE = 1;         //Holds the numerical version of the enum CARD_STATE for IN_HAND

//***********************************************

class Hand {
private:
    Hand(Deck& /*in&out*/);                                 //Constructor - Gets a hand of cards

//******
    void GetHand(Deck&/*in&out*/);             //Function called by hand - generates a hand and returns it to the vector

//******
    void DrawCard(int,/*in*/ Deck&/*in&out*/);              //Interacts with the deck and draws cards from it

//******
    void Discard(std::vector<int>,/*in*/ Deck&/*in&out*/);  //Passes a list of all cards to be discarded and discards them before drawing more

//******
    ~Hand();

public:
    std::vector<Card> vCards;

};

#endif //HAND_H
