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

    Card::Card() { }                //Default constructor - Does nothing as of yet

//******
    Card::Card(int iSuitIn, int iNumIn) {   //Non-default constructor - Creates the card, uses the input parameter
                                            //...to generate suit and rank value.
        SetSuit(iSuitIn);
        SetNum(iNumIn);
        state = IN_DECK;
    }
//******
    CardSuit GetSuit(){             //Returns the card's suit to the calling function
        return suit;
    }
//******
    CardNum GetNum(){               //Returns the card's num to the calling function
        return num;
    }
//******
    std::string GetSuitStr(){       //Returns a str version of suit to calling function
        return suitStr;
    }
//******
    std::string GetNumStr(){        //Returns a str version of rank to the calling function
        return numStr;
    }
//******
    void SetSuit(int iSuitIn) {         //Sets the suit to the input parameter
        suit = CardSuit(iSuitIn);
        suitStr = SUIT_STR[iSuitIn];
    }
//******
    void SetNum(int iNumIn) {           //Sets the rank to the input parameter
        num = CardNum(iSuitIn);
        numStr = NUM_STR[iNumIn];
    }
//******
    ~Card();

/*
    CardSuit suit;
    CardNum num;
    std::string suitStr;
    std::string cardStr;
    CardState state;
*/
