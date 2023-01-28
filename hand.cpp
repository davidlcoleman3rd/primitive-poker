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
    void Hand::DrawCard(int iCount, Deck& dInput) {
        for (int iter = 0; iter < iCount; iter++) {
            vCards.push_back(dInput.DealCard(HAND_STATE));
        }
    }

//******
    void Hand::Discard(std::vector<Card> vDiscard, Deck& dInput) {
        std::vector<Card>::iterator iter;
        for (iter = vDiscard.begin(); iter < vDiscard.end(); iter++) {
            std::vector<Card>::iterator discarder
            for (int iSelect = 0; iSelect < vCard.size(); iSelect++) {
                if (vCard.at(iSelect) == *iter) {
                    vCard.erase(iter);
                }
            }
        }
        DrawCard(iSize, dInput);
    }

//******
    Hand::~Hand() {

    }

public:
    std::vector<Card> vCards;

};
