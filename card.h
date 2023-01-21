//***********************************************
//      CARD CLASS                              *
//                                              *
//***********************************************
//                                              *
//  This C++ class serves as the building block *
//  of a card game - such as poker, spades,     *
//  etc. - consisting of a class for the cards  *
//  themselves, and the definition for critical *
//  enums related to cards in a card game       *
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

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <iomanip>
#include <string>

//***********************************************

enum CardSuit {CLUBS, DIAMONDS, HEARTS, SPADES};            //The suit of each card object
enum CardNum {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,    //The rank of each card object
              NINE, TEN, JACK, QUEEN, KING, ACE};
enum CardState {IN_DECK, IN_HAND, IN_RIVER, IN_DISCARD};

const std::string SUIT_STR[4] = {"CLB", "DMD", "HRT", "SPD"};           //String versions of suit...
const std::string NUM_STR[13] = {" 2 ", " 3 ", " 4 ", " 5 ", " 6 ",     //...and rank.  Translate directlyu with enum values
                                 " 7 ", " 8 ", " 9 ", " 10", "JAC",
                                 "QUE", "KNG", "ACE"};

const int SUIT_COUNT = (sizeof(SUIT_STR) / sizeof(SUIT_STR[0]);         //Holds total number of suits for each card
const int NUM_COUNT = (sizeof(NUM_STR) / sizeof(NUM_STR[0]));           //Holds total number of possible ranks for each card

//***********************************************

class Card {
public:
    Card();                         //Default constructor - Does nothing as of yet

//******
    Card(int /*in*/, int/*in*/);    //Non-default constructor - Creates the card, uses the input parameter
                                    //...to generate suit and rank value.

//******
    CardSuit GetSuit();             //Returns the card's suit to the calling function

//******
    CardNum GetNum();               //Returns the card's num to the calling function

//******
    std::string GetSuitStr();       //Returns a str version of suit to calling function

//******
    std::string GetNumStr();        //Returns a str version of rank to the calling function

//******
    void SetSuit(int/*in*/);        //Sets the suit to the input parameter

//******
    void SetNum(int/*in*/);         //Sets the rank to the input parameter

//******
    ~Card();

private:
    CardSuit suit;
    CardNum num;
    std::string suitStr;
    std::string numStr;
    CardState state;
};



#endif // CARD_H



