//***********************************************
//      PLAYER CLASS - IMPLEMENTATION           *
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


//******
    float BetCash();                            //The player chooses how much money to bet on a hand

//******
    void GetCash(float/*in*/);                  //The player gets cash in return from the pot when they win

//******
    float CheckCash();                          //Checks the amount of cash a player has

//******
    void Drop(Deck&/*inandout*/) {              //The player can drop up to 3 cards - 4 if holding an ace - and draw that many
        vector<int> vCardsToDrop;
        vector<Card>::iterator vIter = hCards.vCards.begin();
        int iMaxDrop = 3;
        int iDropCount = -1;
        for (vIter; vIter < hCards.vCards.end(); vIter++) {
            if (*vIter.GetNum() == ACE)
                iMaxDrop = 4;
        }
        while (iDropCount < 0 && iDropCount > iMaxDrop) {
            std::cout << "\nEnter how many cards you'd like to drop: \n\n";
            std::cin >> iDropCount;
        }
        for (int iIter = 0; iIter < iDropCount; iIter++) {
            int iCardChoice;
            std::cout << "\nWhich card do you wish to drop? (from left to right, enter 1 through 5)\n\n";
            std::cin >> iCardChoice;
            if (vCardsToDrop.size() == 0)
                vCardsToDrop.push_back(iCardChoice);
            else {
                int iTemp = vCardsToDrop.size() + 1;
                int iNeg = (vCardsToDrop.size() * (-1));
                int iHandSize = hCards.vCards.size() - iTemp + 1;
                iCardChoice = iCardChoice - iTemp;
                if (iCardChoice < iHandSize && iCardChoice > iNeg)
                    std::cout << "\nYou already chose that card.\n";
                else if (iCardChoice <= iNeg)
            }
        }
    }

//******
    void Fold(){                                //The player can forfeit their hand until the end of the round and get a new hand
                                //NEED TO IMPLEMENT DISCARD PILE
    }

//******
    Hand Play() {                               //The player plays their sorted hand
        return hCards;
    }

//******
    Player::~Player() {  }                      //Destructor - currently does nothing

/*
private:
    Hand hCards(Deck& dInput);
    float fCash;

};

*/
