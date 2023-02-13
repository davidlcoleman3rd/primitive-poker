




#include <iostream>
#include "card.h"
#include "deck.h"
#include "hand.h"



int main() {
    int playerPoints = 0;

    Deck myDeck;
    myDeck.Shuffle();
    Hand myHand(myDeck);
    myHand.SortHand();
    myHand.PrintHand();

    playerPoints = myHand.CountPoints();

    std::cout << "\n\nPlayer has " << playerPoints << " points this hand.\n\n";

    return 0;
}
