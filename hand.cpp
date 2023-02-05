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

//***********************************************

#include "hand.h"

//***********************************************

    Hand::Hand(Deck& dInput) {
        GetHand(dInput);
    }

//******
    void Hand::GetHand(Deck& dInput) {
        DrawCard(5, dInput);
    }

//******
    void Hand::SortHand() {
        std::vector<Card> vTempSort;                                //
        int iSize = vCards.size();
        CardNum cnFinal;
        Card* tempCard;
        for (int iCount = 0; iCount < iSize; iCount++) {
            for (const auto iter : vCards) {
                CardNum cnTemp;
                cnTemp = vCards.at(iter).GetNum();
                if (cnTemp > cnFinal) {
                    cnFinal = cnTemp;
                    tempCard = vCards.at(iter);
                }
            }
            vTempSort.push_back(tempCard);
            vCards.pop_back();
        }
        vCards = vTempSort;
        tempCard = nullptr;
        delete tempCard;
    }

//******
    void Hand::DrawCard(int iCount, Deck& dInput) {
        for (int iter = 0; iter < iCount; iter++) {
            vCards.push_back(dInput.DealCard(HAND_STATE));
        }
    }

//******
    void Hand::Discard(std::vector<int> vDiscard, Deck& dInput) {
        int iSize = 0;
        std::vector<int>::iterator iter;
        for (iter = vDiscard.begin(); iter < vDiscard.end(); iter++) {
            vCards.erase(vCards.begin() + *iter);
            iSize++;
        }
        DrawCard(iSize, dInput);                        //Draws cards for the user
    }

//******
    Hand::~Hand() {

    }
