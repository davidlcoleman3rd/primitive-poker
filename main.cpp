




#include <iostream>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "circularlList.h"

struct Score {
    int playerNum;
    float points;
};

int main() {

    Deck myDeck;
    myDeck.Shuffle();
    std::vector<Score> vPlayerScore(PLAYER_COUNT);
    std::vector<Player*> playerPtr(PLAYER_COUNT);

    for (int iter = 0; iter < PLAYER_COUNT; iter++) {
        playerPtr[iter] = new Player(myDeck, 500.00);
        vPlayerScore[iter].playerNum = iter + 1;
        vPlayerScore[iter].points = playerPtr[iter]->HandPoints();
    }

    CircularList<Player*> turnOrder (playerPtr[0]);
    for (int iter = 1; iter < PLAYER_COUNT; iter++) {
        turnOrder.NewNode(playerPtr[iter]);
    }

    turnOrder.TraverseStart();
    for (int iter = 1; iter <= PLAYER_COUNT; iter++) {
        std::cout << "~~~~~~\nPlayer " << iter << ":\n\n";
        turnOrder.GetPlayer()->PlayHand(false);
        turnOrder.TraverseNext();
    }

    int tempMax = 0;
    int tempPos = 0;
    for (int iter = 0; iter < PLAYER_COUNT; iter++) {
        if (vPlayerScore[iter].points >= tempMax) {
            tempMax = vPlayerScore[iter].points;
            tempPos = vPlayerScore[iter].playerNum;

        }
    }

    std::cout << "Player " << tempPos << " is the winner of the hand!\n\n";

    for (auto i : playerPtr) {
        delete i;
    }

    playerPtr.clear();
/*
    const double ONE = 1.0;

    std::cout.precision(14);
    std::cout << std::fixed << 1.0 / std::pow(13,0) << "\n"
              << ONE / std::pow(13,1) << "\n"
              << ONE / std::pow(13,2) << "\n"
              << ONE / std::pow(13,3) << "\n"
              << ONE / std::pow(13,4) << "\n"
              << ONE / std::pow(13,5) << "\n"
              << ONE / std::pow(13,6) << "\n"
              << ONE / std::pow(13,7) << "\n"
              << ONE / std::pow(13,8) << "\n"
              << ONE / std::pow(13,9) << "\n"
              << ONE / std::pow(13,10) << "\n"
              << ONE / std::pow(13,11) << "\n"
              << ONE / std::pow(13,12) << "\n\n";
*/
    return 0;
}

