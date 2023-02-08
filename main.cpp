




#include <iostream>
#include "card.h"
#include "deck.h"
#include "hand.h"



int main() {

    Deck myDeck;
    myDeck.Shuffle();
    Hand myHand(myDeck);
    myHand.PrintHand();

    return 0;
}
