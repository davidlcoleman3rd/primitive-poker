
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
        Card* tempPtr = nullptr;
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
        Card* tempPtr = nullptr;                    //CURRENTLY IS USED FOR TESTING PURPOSES

        tempPtr = new Card(SPADES, TWO);
        stDeck.push(*(tempPtr));
        delete tempPtr;
        tempPtr = nullptr;

        tempPtr = new Card(SPADES, KING);
        stDeck.push(*(tempPtr));
        delete tempPtr;
        tempPtr = nullptr;

        tempPtr = new Card(SPADES, QUEEN);
        stDeck.push(*(tempPtr));
        delete tempPtr;
        tempPtr = nullptr;

        tempPtr = new Card(SPADES, JACK);
        stDeck.push(*(tempPtr));
        delete tempPtr;
        tempPtr = nullptr;

        tempPtr = new Card(SPADES, TEN);
        stDeck.push(*(tempPtr));
        delete tempPtr;
        tempPtr = nullptr;

    }

//******
    Deck::Deck(bool test) {                                                 //Alternative constructor - used to generate a deck for testing purposes
        Card* tempPtr = nullptr;
        for (int iIterSuit = 0; iIterSuit < 2; iIterSuit++) {
                tempPtr = new Card(0, 2);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(1, 2);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(2, 2);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(0, 5);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(1, 5);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(0, 7);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(1, 7);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(0, 9);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(1, 9);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(2, 9);
                stDeck.push(*(tempPtr));
    }
    delete tempPtr;
}

//******
    Deck::Deck(char test) {                                                 //Alternative constructor - used to generate a deck for testing purposes
        Card* tempPtr = nullptr;
        for (int iIterSuit = 0; iIterSuit < 2; iIterSuit++) {

                tempPtr = new Card(3, 12);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 0);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 1);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 2);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 3);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(0, 12);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(1, 0);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(2, 1);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(0, 2);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(1, 3);
                stDeck.push(*(tempPtr));
    }

                tempPtr = new Card(3, 12);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 0);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 1);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 2);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 3);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 12);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 0);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 1);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 2);
                stDeck.push(*(tempPtr));

                tempPtr = new Card(3, 3);
                stDeck.push(*(tempPtr));

    delete tempPtr;
}

Deck::Deck(std::string test) {
    Card* tempPtr = nullptr;
    tempPtr = new Card(3, 0);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 1);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 2);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 3);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 4);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 5);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 6);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 7);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 8);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 9);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 10);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 11);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(3, 12);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 1);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 2);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 3);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 4);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 5);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 6);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 7);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 8);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 9);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 10);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 11);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(0, 12);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 1);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 2);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 3);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 4);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 5);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 6);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 7);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 8);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 9);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 10);
    stDeck.push(*(tempPtr));
    tempPtr = new Card(1, 11);
    stDeck.push(*(tempPtr));
    delete tempPtr;
}



//******
    void Deck::Shuffle() {                                  //Shuffles the deck x times, where x is the argument passed to the function - REMOVED X TIMES PARAMETER FOR TESTING PURPOSES
        int tempSize = GetSize();
        std::random_device shuffler;                        //Random device
        std::mt19937 seedMake(shuffler());                  //Random device seed
        std::vector<Card*> vTemp(tempSize, nullptr);         //Vector to hold the card values
        std::uniform_int_distribution<int> randInt(0,(tempSize - 1));       //The object that produces our random number
        Card* tempPtr = nullptr;
        while (stDeck.size() > 0) {
            int iTemp = randInt(seedMake);
            if (vTemp.at(iTemp) == nullptr) {
               tempPtr = new Card(stDeck.top());
               vTemp.at(iTemp) = tempPtr;
               stDeck.pop();
               tempPtr = nullptr;
            }
        }
        for (int iter = 0; iter < tempSize; iter++) {
            std::stack<Card> stTemp;
            Card cTemp(*(vTemp.at(iter)));
            stDeck.push(cTemp);
        }
        for (auto p : vTemp) {
            delete p;
        }
        vTemp.clear();
    }

//******
    Card Deck::DealCard(int iInState/*in*/){        //Peeks a card from the top of the deck and distributes it to a player, popping it from deck
        if (GetSize() == 0) {
            Reshuffle();
        }
        Card cTemp(stDeck.top());
        stDeck.pop();
        cTemp.SetState(CardState(iInState));
        return cTemp;
    }

//******
    int Deck::GetSize() {
        return stDeck.size();
    }

//******
    void Deck::Reshuffle() {
        while (disPile.GetSize() > 0) {
            stDeck.push(disPile.GetTop());
            disPile.Pop();
        }
        Shuffle();
    }

//******
    void Deck::ToDiscard(Card cInput) {
        disPile.Push(cInput);
    }

//******
    int Deck::DiscardSize() {
        return disPile.GetSize();
    }

//******
   // Deck::~Deck(){           //Destructor, currently does nothing

    //}

/*
private:
    stack<Card> stDeck;
};
*/
