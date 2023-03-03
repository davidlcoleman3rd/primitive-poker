




#include <iostream>
#include <limits>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "circularlList.h"

struct Score {
    int playerNum;
    double points;
};

const int ANTE = 5;

//*****************************************

int main() {
    bool gameLoop = true;
    Deck myDeck;
    myDeck.Shuffle();
    float myPot = 0;
    std::vector<Score> vPlayerScore(PLAYER_COUNT);
    std::vector<Player*> playerPtr(PLAYER_COUNT);
    int betIteration = 0;

    for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            playerPtr[iter] = new Player(myDeck, 500.00);
        }

    while (gameLoop) {
        std::cout << "\nThere is a $" << ANTE << " ante for this hand.\n\n";
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            vPlayerScore[iter].playerNum = iter + 1;
            vPlayerScore[iter].points = playerPtr[iter]->HandPoints();
        }

        std::string playerChoice;

        CircularList<Player*> turnOrder (playerPtr[0]);
        for (int iter = 1; iter < PLAYER_COUNT; iter++) {
            turnOrder.NewNode(playerPtr[iter]);
        }

        turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            myPot += float(turnOrder.GetPlayer()->AnteUp(ANTE));
            turnOrder.TraverseNext();
        }

        std::cout << "The pot = " << std::fixed << std::setprecision(2) << "$" << myPot << "\n\n";

        turnOrder.TraverseStart();
        for (int iter = 1; iter < 1 + 1; iter++) {
            std::cout << "~~~~~~\nPlayer " << iter << ":\n\n";
            turnOrder.GetPlayer()->PlayHand();
        }

        turnOrder.TraverseStart();
        turnOrder.GetPlayer()->DiscardCards(myDeck);
        vPlayerScore[0].points = playerPtr[0]->HandPoints();

        turnOrder.TraverseStart();
        for (int iter = betIteration; iter > 0; iter--) {
            turnOrder.TraverseNext();
        }

        float callValue = 0;
        std::vector<bool> allCalled(PLAYER_COUNT, false);
        bool callingBets = true;
        if (betIteration > 0) {
            callValue = turnOrder.GetPlayer()->BetCash(betIteration + 1, true, myDeck);
            allCalled.at(betIteration) = true;
        }
        else {
            callValue = turnOrder.GetPlayer()->BetCash(myDeck);
            myPot += callValue;
        }
        while (callingBets) {
            float temp = 0;
            betIteration++;
            if (betIteration == PLAYER_COUNT) {
                betIteration = 0;
            }
            turnOrder.TraverseNext();
            if (betIteration == 0) {
                temp = turnOrder.GetPlayer()->CallBet(callValue, myDeck);           //FUNCTION NEEDS DEFINITION
                if (turnOrder.GetPlayer()->FoldedHand()) {                          //FUNCTION NEEDS DEFINITION
                    allCalled.at(betIteration) = true;
                }
                else if (temp > callValue) {
                    callValue = temp;
                    for (auto i : allCalled) {
                        i = false;
                    }
                    allCalled.at(betIteration) = true;
                    myPot += turnOrder.GetPlayer()->TakeWager(temp);                //FUNCTION NEEDS DEFINITION
                }
                else if (temp == callValue) {
                    allCalled.at(betIteration) = true;
                    myPot += turnOrder.GetPlayer()->TakeWager(temp);
                }
            }
            else {
                temp = turnOrder.GetPlayer()->CallBet(callValue, betIteration + 1, true, myDeck);       //FUNCTION NEEDS DEFINITION
                if (turnOrder.GetPlayer()->FoldedHand()) {
                    allCalled.at(betIteration) = true;
                }
                else if (temp > callValue) {
                    callValue = temp;
                    for (auto i : allCalled) {
                        i = false;
                    }
                    allCalled.at(betIteration) = true;
                    myPot += turnOrder.GetPlayer()->TakeWager(temp);
                }
                else if (temp == callValue) {
                    allCalled.at(betIteration) = true;
                    myPot += turnOrder.GetPlayer()->TakeWager(temp);
                }
            }
            callingBets = false;
            for (auto i : allCalled) {
                if (i = false) {
                    callingBets = true;
                }
            }
        }

        betIteration++;
        if (betIteration == (PLAYER_COUNT)) {
            betIteration = 0;
        }

        std::cout << "\nHow much do you bet on this hand?\n\n";
        for (int iter = 1; iter <= PLAYER_COUNT; iter++) {
            std::cout << "~~~~~~\nPlayer " << iter << ":\n\n";
            turnOrder.GetPlayer()->PlayHand();
            turnOrder.TraverseNext();
        }

        int tempMax = 0;
        int tempPos = 0;
        turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            if (vPlayerScore[iter].points >= tempMax) {
                tempMax = vPlayerScore[iter].points;
                tempPos = vPlayerScore[iter].playerNum;

            }
        }

        std::cout << "Player " << tempPos << " is the winner of the hand!\n\n";
        turnOrder.TraverseStart();
        for (int iter = 1; iter < tempPos; iter++) {
            turnOrder.TraverseNext();
        }
        turnOrder.GetPlayer()->GetCash(myPot);
        myPot = 0;

        turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            std::cout << "Player " << iter + 1 << " has $" << turnOrder.GetPlayer()->CheckCash() << "\n";
            turnOrder.TraverseNext();
        }
        std::cout << "\n";
        turnOrder.TraverseStart();
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
            char choiceAuto = playerChoice.at(0);
            tolower(choiceAuto);
            switch(choiceAuto) {
                case 'y' : {
                    for (auto i : playerPtr) {
                        i->DiscardHand(myDeck);
                    }
                    myDeck.Reshuffle();

                    for (auto i : playerPtr) {
                        i->NewHand(myDeck, false);
                    }
                    choiceLoop = false;
                    break;
                }
                case 'n' : {
                    choiceLoop = false;
                    gameLoop = false;
                    for (auto i : playerPtr) {
                        i->DiscardHand(myDeck);
                        delete i;
                    }
                    playerPtr.clear();
                    break;
                }
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

