




#include <iostream>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "circularlList.h"



int main() {

    Deck myDeck;
    myDeck.Shuffle();

    std::vector<Player*> playerPtr(4);
    for (int iter = 0; iter < PLAYER_COUNT; iter++) {
        playerPtr[iter] = new Player(myDeck, 500.00);
    }

    CircularList<Player*> turnOrder (playerPtr[0]);
    for (int iter = 1; iter < PLAYER_COUNT; iter++) {
        turnOrder.NewNode(playerPtr[iter]);
    }
    for (int iter = 1; iter <= PLAYER_COUNT; iter++) {
        std::cout << "~~~~~~\nPlayer " << iter << ":\n\n";
        turnOrder.GetPlayer()->PlayHand();
        turnOrder.TraverseNext();
    }


    return 0;
}
