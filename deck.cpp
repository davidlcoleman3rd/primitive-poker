
//***********************************************
//      DECK CLASS IMPLEMENTATION               *
//                                              *
//***********************************************
//                                              *
//  This C++ class serves as a stack structure  *
//  of card objects.  This is the main source   *
//  card objects that players will draw from    *
//  when playing the game.                      *
//                                              *
//***********************************************
//  Version 0.0.4.1 pushed by David Coleman III *
//  on  01 - 24 - 23                            *
//***********************************************



//***********************************************

#include "deck.h"

//***********************************************

//const int DECK_SIZE = 52;       //The total number of cards in a deck


//***********************************************

    Deck::Deck() {
        Card* tempPtr;
        for (int iIterSuit = 0; iIterSuit < MAX_SUITS; iIterSuit++) {
            for (int iIterRank = 0; iIterRank < MAX_RANKS; iIterRank++) {
                tempPtr = new Card(iIterSuit, iIterRank);
                stDeck.push(*(tempPtr));
            }
        }
        delete tempPtr;
    }

//******
    Deck::Deck(int/*in*/) {                         //Alternative constructor - Generates a deck made of X decks of cards (TO BE IMPLEMENTED LATER);

    }

//******
    void Deck::Shuffle() {                                  //Shuffles the deck x times, where x is the argument passed to the function - REMOVED X TIMES PARAMETER FOR TESTING PURPOSES
        std::random_device shuffler;                        //Random device
        std::mt19937 seedMake(shuffler());                  //Random device seed
        std::vector<Card*> vTemp(100, nullptr);              //Vector to hold the card values
        std::uniform_int_distribution<int> randInt(0,51);   //The object that produces our random number
       // std::cout << "\ntest 01\n";
        Card* tempPtr = nullptr;
        while (stDeck.size() > 0) {
            int iTemp = randInt(seedMake);
           // std::cout << "\ntest 02\n";
            if (vTemp.at(iTemp) == nullptr) {
               // std::cout << "\ntest 03\n";
                tempPtr = vTemp.at(iTemp);
               // std::cout << "\ntest 05\n";
               //std::cout << "\ntop = " << stDeck.top().GetNumStr() << "\n";
               //std::cout << "\niter " << stDeck.size() << "\n";
               //std::cout << "itemp = " << iTemp << "\n";
               Card cTemp(stDeck.top());
               //std::cout << "\nTest again\n";
                vTemp.at(iTemp) = &cTemp;
              //std::cout << "\ntest 06\n";
             //vTemp.at(iTemp) = tempPtr;
               // std::cout << "\ntest 07\n";
             tempPtr = nullptr;
               //std::cout << "\ntest 04\n";
                stDeck.pop();
             //  std::cout << "\ntest 05\n";
            }
        }
 //       int iTemp = vTemp.size();
        for (int iter = 51; iter >= 0; iter--) {
           // std::cout << "new test " << iter << '\n';
            tempPtr = vTemp.at(iter);
            std::cout << "new top is " << tempPtr->GetNumStr() << '\n';
            stDeck.push(*(tempPtr));
            std::cout << "new card is " << stDeck.top().GetNumStr() << '\n';
           // std::cout << "new test 03" << '\n';
         //   std::cout << "new test 04" << '\n';
       //     std::cout << "new test 05" << '\n';
        }
        vTemp = std::vector<Card*>();
    }

//******
    Card Deck::DealCard(int iInState/*in*/){        //Peeks a card from the top of the deck and distributes it to a player, popping it from deck
        Card cTemp(stDeck.top());
        stDeck.pop();
        cTemp.SetState(CardState(iInState));
        return cTemp;
    }

//******
    Deck::~Deck(){                                  //Destructor, currently does nothing

    }

/*
private:
    stack<Card> stDeck;
};
*/
