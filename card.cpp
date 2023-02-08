//***********************************************
//      CARD CLASS (IMPLEMENTATION)             *
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
//  Version 0.0.4.1 pushed by David Coleman III *
//  on  01 - 24 - 23                            *
//***********************************************

    #include "card.h"

//***********************************************

    Card::Card() { }                    //Default constructor - Does nothing as of yet

//******
    Card::Card(const Card& cOther) {    //Copy constructor - Creates a new object by copying the cOther
        Card& temp = const_cast <Card&>(cOther);
        SetSuit(int(temp.GetSuit()));
        SetNum(int(temp.GetNum()));
        SetState(temp.GetState());
    }

//******
    Card::Card(int iSuitIn, int iNumIn) {   //Non-default constructor - Creates the card, uses the input parameter
                                            //...to generate suit and rank value.
        SetSuit(iSuitIn);
        SetNum(iNumIn);
        state = IN_DECK;
    }
//******
    CardSuit Card::GetSuit(){             //Returns the card's suit to the calling function
        return suit;
    }
//******
    CardNum Card::GetNum(){               //Returns the card's num to the calling function
        return num;
    }
//******
    std::string Card::GetSuitStr(){       //Returns a str version of suit to calling function
        return suitStr;
    }
//******
    std::string Card::GetNumStr(){        //Returns a str version of rank to the calling function
        return numStr;
    }
//******
    void Card::SetSuit(int iSuitIn) {         //Sets the suit to the input parameter
        suit = CardSuit(iSuitIn);
        suitStr = SUIT_STR[iSuitIn];
    }
//******
    void Card::SetNum(int iNumIn) {           //Sets the rank to the input parameter
        num = CardNum(iNumIn);
        numStr = NUM_STR[iNumIn];
    }

//******
    void Card::SetState(CardState inState) {    //Sets the current card state
        state = inState;
    }

//******
    CardState Card::GetState() {                //Gets the current card state
        return state;
    }

//******
    Card::~Card() {  }

/*
    CardSuit suit;
    CardNum num;
    std::string suitStr;
    std::string cardStr;
    CardState state;
*/
