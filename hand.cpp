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
        std::vector<Card> vTempSuit;
        std::list<Card> vTempRank;
        for (int iter = 0; iter < 4; iter++) {
            for (const auto suitCheck : vCards) {
                if (suitCheck->GetSuit() == CardSuit(iter)) {
                    vTempSuit.push_back(vCards[iter]);
                }
            }
            for (const auto rankCheck : vTempSuit) {
                if (vTempRank.size() == 0) {
                    vTempRank.push_back(vTempSuit[rankCheck]);
                }
                else if(vTempSuit[rankCheck] >= vTempRank) {
                    vTempRank.push_back(vTempSuit[rankCheck]);
                }
                else {
                    vTempRank.push_front(vTempSuit[rankCheck]);
                }
            }
        }
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
        DrawCard(iSize, dInput);
    }

//******
    Hand::~Hand() {

    }
