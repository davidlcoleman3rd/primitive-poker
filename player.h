//***********************************************
//      PLAYER CLASS                            *
//                                              *
//***********************************************
//                                              *
//  This C++ class serves as a structure for    *
//  each individual player at the game table    *
//                                              *
//***********************************************
//  Version 0.0.4.1 pushed by David Coleman III *
//  on  01 - 24 - 23                            *
//***********************************************

#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

//***********************************************\


class Player {
public:
    Player(Deck&/*in&out*/, float/*in*/);       //Generates a player, gives them a hand of 5 cards and a sum of cash

//******
    float BetCash();                            //The player chooses how much money to bet on a hand

//******
    void GetCash(float/*in*/);                  //The player gets cash in return from the pot when they win

//******
    float CheckCash();                          //Checks the amount of cash a player has

//******
    void Drop(Deck&/*inandout*/);               //The player can drop up to 3 cards - 4 if holding an ace - and draw that many

//******
    void Fold();                                //The player can forfeit their hand until the end of the round and get a new hand

//******
    Hand Play();                                //The player plays their sorted hand

//******
    ~Player();                                  //Destructor - currently does nothing

private:
    Hand* hCards;
    float fCash;
    bool bFolded;
};

#endif // PLAYER_H
