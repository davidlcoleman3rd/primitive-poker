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
        Card* tempCard = nullptr;
        for (int iCount = 0; iCount < iSize; iCount++) {
            int vCardSize = vCards.size();
            for (int iter = 0; iter < vCardSize; iter++) {
                CardNum cnFinal;
                CardNum cnTemp;
                cnTemp = vCards.at(iter).GetNum();
                Card cardTemp(vCards.at(iter));
                if (cnTemp > cnFinal || iter == 0) {
                    if (tempCard != nullptr) {
                        delete tempCard;
                        tempCard = nullptr;
                    }
                    cnFinal = cnTemp;
                    std::cout << "\nTest 01\n";
                    tempCard =  new Card(cardTemp);
                    std::cout << "\nTest 02\n";
                }
            }
            vTempSort.push_back(*(tempCard));
            for (int iter = 0; iter < int(vCards.size()); iter++) {
                if (vCards.at(iter) == *(tempCard)) {
                    vCards.erase(vCards.begin() + iter);
                }
            }
            delete tempCard;
            tempCard = nullptr;
        }
        vCards = vTempSort;
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
    void Hand::PrintHand() {
        std::cout << "Your hand:\n\n";
        for (auto& iter : vCards) {
            std::cout << iter.GetNumStr() << " of " << iter.GetSuitStr() << '\n';
        }
        std::cout << '\n';
    }

//******
    Hand::~Hand() {

    }
