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

    #include "player.h"

//******
    Player::Player(Deck& dDeck,/*in&out*/ float fStartCash/*in*/) {
        fCash = fStartCash;                                                     //Starts each player off with a set amount of money
        hCards = new Hand(dDeck);                                               //Generates a hand of 5 cards for each player
        bFolded = false;                                                        //Sets the "folded" state to false - used to check if the player has folded this turn
    }

//******
 //   float Player::BetCash() {                                                   //The player chooses how much money to bet on a hand
    //    float fTempCash = fCash + 1;                                            //Sets temp cash just out of range to prime loop
  //      while (fTempCash > fCash || fTempCash < 0) {                            //Loop repeats until fTempCash is a valid amount (greater than or equal to 0 and less than total cash)
     //       std::cout << "\nEnter how much money you bet. Type 0 to fold.\n";
      //      std::cin >> fTempCash;
       //     if (fTempCash = 0) {                                                //If the player enters 0, they fold their hand
         //       Fold();
        //        break;
         //   }
       // }
       // fCash -= fTempCash;                                                     //Subtracts the total amount to be bet from the total cash the player has
       // return fTempCash;                                                       //Returns this value to the calling function    -   POT SHOULD BE CALLING OBJECT
  //  }
//******
    void Player::GetCash(float fCashIn/*in*/) {                     //The player gets cash in return from the pot when they win
        fCash += fCashIn;
    }

//******
    float Player::CheckCash() {                                     //Checks the amount of cash a player has
        return fCash;
    }

//******

//     void Player::Drop(Deck&/*inandout*/) {                          //The player can drop up to 3 cards - 4 if holding an ace - and draw that many
/*
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
*/

//******
//    void Player::Fold(Discard& diPile/*out*/){                  //The player can forfeit their hand until the end of the round and get a new hand
 //       while (hCards.size() > 0) {
  //          diPile.GetCard(hCards[hCards.size() - 1]);
   //         hCards.pop_back();
  //      }
   //     bFolded = true;
    //}

//******
//    bool Player::GetFoldStatus() {
  //      return bFolded;
 //   }

//******
    void Player::PlayHand() {                                   //Sorts the player's hand based on suit first, and then rank. Used to generate a point value from the hand
        hCards->SortHand();
        hCards->PrintHand();
        std::cout << "\n" << hCards->CountPoints() << " points\n\n";
    }

//******
//    int Player::HandPoints() {                                  //Generates a "value" of the sorted hand
//
//    }

//******
    //Hand Play() {                               //The player plays their sorted hand
    //    return hCards;
    //}

//******
    Player::~Player() {
        delete hCards;
    }                      //Destructor - currently does nothing

/*
private:
    Hand hCards(Deck& dInput);
    float fCash;

};

*/
