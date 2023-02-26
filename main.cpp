




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
    bool gameLoop = true;
    Deck myDeck;
    myDeck.Shuffle();
    while (gameLoop) {
        std::string playerChoice;

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
        for (int iter = 1; iter < 1 + 1; iter++) {
            std::cout << "~~~~~~\nPlayer " << iter << ":\n\n";
            turnOrder.GetPlayer()->PlayHand(false);
        }

        turnOrder.TraverseStart();
        turnOrder.GetPlayer()->DiscardCards(myDeck);

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
            i->DiscardHand(myDeck);
            delete i;
        }

        playerPtr.clear();
        bool choiceLoop = true;
        std::cout << "\n\nDeck size: " << myDeck.GetSize() << "\n"
                  << "\nDiscard size: " << myDeck.DiscardSize() << "\n\n";
        while (choiceLoop) {
            std::cout << "Would you like to play again?\n"
                      << "Type <yes> to play again, or <no> to quit\n\n";
            if(playerChoice == "") {
                std::cin.ignore(1000, '\n');
            }
            getline(std::cin, playerChoice);
            char choiceAuto = tolower(playerChoice.at(0));
            tolower(choiceAuto);
            switch(choiceAuto) {
                case 'y' : choiceLoop = false; break;
                case 'n' : choiceLoop = false; gameLoop = false; break;
                default : {
                    std::cout << "\nInvalid entry, try again\n";
                    break;
                }
            }
        }
        playerChoice = "";
    }
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
    std::cout << "\nGoodbye!!\n";
    return 0;
}

