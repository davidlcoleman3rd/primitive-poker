




#include <iostream>                 //For output to the terminal - cout, cin, getline(), setw, etc.
#include <limits>                    //For making sure points are allocated correctly - used for int and float lims
#include "card.h"                   //Card class - These objects are the main building block of the entire game set
#include "deck.h"                   //Deck class - The main point in which cards are drawn and distributed to each player
#include "hand.h"                   //Hand class - The main body by which the player stores their cards
#include "player.h"                 //Player class - the class that serves to represent each plyaer in the game; CPU or physical
#include "circularlList.h"          //circular linked list implementation - used to get and maintain the correct turn order for all
                                    //...players in a single game of poker

struct Score {                      //Score struct - used to represent the value of each players hand and compare to others
    int playerNum;                      //Shows the particular player that a score represents
    double points;                      //Stores the actual amount of points each player has - used to evaluate a hand of cards
};

const int ANTE = 5;                 //Constant for ante - the amount of money each player has to put into the pot in order to participate

//*****************************************


int main() {
    bool gameLoop = true;           //Bool that makes sure the game continues to run even after a floor has completed
    Deck myDeck;                    //Stack structure - is both the games stack of cards and the games discard pile
    myDeck.Shuffle();               //Shuffles the deck into a random order
    float myPot = 0;                                //The pot - serves as the storage place for all money wagered by the player
    std::vector<Score> vPlayerScore(PLAYER_COUNT);  //A vector of playerScores - one for each player
    std::vector<Player*> playerPtr(PLAYER_COUNT);   //A vector of player pointers - used to generate circular linked list
    std::vector<PlayerPerception> playerTells;
    int currBet = 0;                                //This will be used to rotate the active betting player clockwise each floor
    int betIteration = 0;                           //This will be used to move afloor the table during the rais and call phase of betting

    for (int iter = 0; iter < PLAYER_COUNT; iter++) {           //This loop will generate the players at the table - one physical, and 3 CPU
            if (iter == 0) {
                playerPtr[iter] = new Player(myDeck, 500.00);
            }
            else {
                playerPtr[iter] = new CPU(myDeck, 500.00);
            }
        }

    while (gameLoop) {                                                              //The game will continue to run until the loop is broken
        std::cout << "\nThere is a $" << ANTE << " ante for this hand.\n\n";
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {                           //The player's score is generated based on the value
            vPlayerScore[iter].playerNum = iter + 1;                                //...of the cards in their hand
            vPlayerScore[iter].points = playerPtr[iter]->HandPoints();
        }

        std::string playerChoice;                                                   //Used for player input

        CircularList<Player*> turnOrder (playerPtr[0]);                             //Uses the first player to generate the turn order
        for (int iter = 1; iter < PLAYER_COUNT; iter++) {                           //Fills the turn order object with all players
            turnOrder.NewNode(playerPtr[iter]);
        }

        turnOrder.TraverseStart();                                                  //Begins the turn order at the beginning
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {                           //Loops until it receives an ante from every player
            myPot += float(turnOrder.GetPlayer()->AnteUp(ANTE));                    //Gets the ante from each player
            turnOrder.TraverseNext();                                               //Moves to the next player
        }

        std::cout << "The pot = " << std::fixed << std::setprecision(2) << "$" << myPot << "\n\n";

        turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            std::cout << "\nPlayer " << iter + 1 << " is dealt their cards...";
            if (iter == 0) {
                playerTells.push_back(AVERAGE);
                std::cout << "\nYou receive your cards.\n\n";
            } else {
                CPU* tempPtr = dynamic_cast<CPU*>(turnOrder.GetPlayer());
                playerTells.push_back(tempPtr->JudgeHand());
                tempPtr = nullptr;
            }
            turnOrder.TraverseNext();
        }



        turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            for (int next = 1; next < PLAYER_COUNT; next++) {
                int temp = iter + next;
                std::cout << "\nFirst Temp = " << temp << "\n\n";
                if (temp >= PLAYER_COUNT) {
                    temp -= PLAYER_COUNT;
                    std::cout << "\nSecond Temp = " << temp << "\n\n";
                }
                std::cout << "\nThird Temp = " << temp << "\n\n";
                turnOrder.GetPlayer()->SetOpinion(playerTells.at(temp));
            }

        }



        turnOrder.TraverseStart();
        for (int iter = 1; iter < 1 + 1; iter++) {                  //Will show the player's hand (NEEDS TO BE CHANGED)
            std::cout << "~~~~~~\nPlayer " << iter << ":\n\n";
            turnOrder.GetPlayer()->PlayHand();
        }

        turnOrder.TraverseStart();
        for (int iter = 1; iter < 5; iter++) {
            std::cout << "\n~~~~~~\nPlayer " << iter << ":\n\n";
            turnOrder.GetPlayer()->PlayHand();
            if (iter == 1) {
                turnOrder.GetPlayer()->DiscardCards(myDeck);
            } else {
                CPU* tempPtr = dynamic_cast<CPU*>(turnOrder.GetPlayer());
                tempPtr->DiscardCards(myDeck);
                tempPtr = nullptr;
            }
            std::cout << "\nNew Hand:\n\n";
            turnOrder.GetPlayer()->PlayHand();
            turnOrder.TraverseNext();
        }

        turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            if (iter == 0) {
                playerTells.push_back(AVERAGE);
                std::cout << "\nYou look at your cards.\n\n";
            } else {
                std::cout << "\nPlayer " << iter + 1 << " looks at their cards...\n";
                CPU* tempPtr = dynamic_cast<CPU*>(turnOrder.GetPlayer());
                playerTells.at(iter) = tempPtr->JudgeHand();
                tempPtr = nullptr;
            }
            turnOrder.TraverseNext();
        }

        vPlayerScore[0].points = playerPtr[0]->HandPoints();        //Evaluates how much each player's hand is worth
        for (int iter = 1; iter < 1 + 1; iter++) {
            std::cout << "~~~~~~\nPlayer " << iter << ":\n\n";
            turnOrder.GetPlayer()->PlayHand();                      //
        }


        turnOrder.TraverseStart();
        for (int iter = currBet; iter > 0; iter--) {
            turnOrder.TraverseNext();
        }

        float callValue = 0;
        std::vector<bool> allCalled(PLAYER_COUNT, false);
        bool firstBet = true;
        bool callingBets = true;
        std::cout << "\ncurrBet check = " << currBet << "\n\n";
        int tempBet = currBet;

        //std::cout << "\nTest 01\n";

        while (firstBet) {
            int checkFold = 0;
            turnOrder.TraverseNext();
            //std::cout << "\nTest 02\n";
            for (int iter = 0; iter < PLAYER_COUNT - 1; iter++) {
                if (turnOrder.GetPlayer()->FoldedHand()) {
                    checkFold++;
                }
                if (checkFold == PLAYER_COUNT - 1) {
                    callingBets = false;
                    firstBet = false;
                }
                turnOrder.TraverseNext();
                //std::cout << "\nTest 03\n";
            }
            std::cout << "\nPlayer " << tempBet + 1 << " is leading the bet this hand\n\n";
            //std::cout << "\nTest 04\n";
            if (firstBet) {
                //std::cout << "\nTest 05\n";
                if (tempBet > 0) {
                    //std::cout << "\nTest 06\n";
                    //std::cout << "\nCash 1 = " << turnOrder.GetPlayer()->CheckCash() << "\n\n";
                    CPU* tempPtr = dynamic_cast<CPU*>(turnOrder.GetPlayer());
                    //std::cout << "\nCash 2 = " << tempPtr->CheckCash() << "\n\n";
                    std::vector<PlayerPerception> tempOpinion;              //A vector of opponents opinions of the player's hand/tells
                    std::vector<int> inBluff;                               //A vector of opponents bluff stat - position matched with tempOpinion
                    std::vector<PlayerPerception> tempPerception;           //A vector of opponents opinions of themselves - position matched with the above
                    std::vector<double> inScores;                           //A vector of opponents hand values; used for player decision making if the player
                                                                            //...rolls exceptionally well.  Position matched with the above temp variables
                    //std::cout << "\nTest 07\n";

                    for (int iter = 0; iter < PLAYER_COUNT; iter++) {
                       // std::cout << "\nTest 08\n";
                        if (iter > 0) {
                           // std::cout << "\nTest 09\n";

                            int next = iter + tempBet;
                                if (next >= PLAYER_COUNT) {
                                    next -= PLAYER_COUNT;
                                   // std::cout << "\nTest 10\n";
                                }
                                //std::cout << "\nTest 11\n";
                            tempPerception.push_back(playerTells.at(next));
                            tempOpinion.push_back(turnOrder.GetPlayer()->GetPlayerTells(PLAYER_COUNT - iter));          //UNDEFINED
                                                                                                                        //Gets opponent opinion of a specific player's tell

                            inBluff.push_back(turnOrder.GetPlayer()->GetBluffStat());                                   //UNDEFINED
                                                                                                                        //Gets opponent's bluff stat

                            inScores.push_back(turnOrder.GetPlayer()->HandPoints());                                    //DEFINED
                                                                                                                        //Gets the actual value of a particular opponents hand

                        }
                        turnOrder.TraverseNext();
                       // std::cout << "\nTest 12\n";
                    }
                   // std::cout << "\nTest 51\n";
                    callValue = tempPtr->BetCash(tempBet + 1, myDeck, tempPerception,
                                                                inScores, inBluff, tempOpinion);
                   // std::cout << "\nTest 52\n";
                    allCalled.at(tempBet) = true;
                   // std::cout << "\nTest 53\n";
                    tempPtr = nullptr;
                    //std::cout << "\nTest 13\n";
                }
                else {
                    callValue = turnOrder.GetPlayer()->BetCash(myDeck);
                    allCalled.at(tempBet) = true;
                    //std::cout << "\nTest 14\n";
                }
            }
            if (turnOrder.GetPlayer()->FoldedHand()) {
                tempBet++;
                //std::cout << "\nTest 15\n";

                if (tempBet >= PLAYER_COUNT) {
                    tempBet = 0;
                   // std::cout << "\nTest 16\n";
                }
                //std::cout << "\nTest 17\n";
            }
            else {
                firstBet = false;
                //std::cout << "\nTest 18\n";
            }
            turnOrder.TraverseNext();
        }

        myPot += callValue;
        betIteration = tempBet;

        while (callingBets) {
            //std::cout << "\n\nPrev call value = " << callValue << "\n";
            std::cout << "\n\nCallValTest 01     " << callValue << "\n\n";
            callValue = std::floor(callValue);
            std::cout << "\n\nCallValTest 02     " << callValue << "\n\n";
            //std::cout << "\nPost call value = " << callValue << "\n\n";
            tempBet++;
            if (tempBet >= PLAYER_COUNT) {
                tempBet -= PLAYER_COUNT;
            }
            //std::cout << "\nTest 19\n";
            float temp = 0;
            betIteration++;
            if (betIteration == PLAYER_COUNT) {
                betIteration = 0;
               // std::cout << "\nTest 20\n";
            }
            std::cout << "\n\nBet iteration = " << betIteration + 1 << "\n\n";
            if (!(turnOrder.GetPlayer()->FoldedHand())) {
                //std::cout << "\nTest 21\n";
                std::cout << "\nPlayer " << betIteration + 1 << " can choose to call, raise, or fold.\n\n";
                if (betIteration == 0) {
                    std::cout << "\n\n\nUSER PLAYER\n\n\n";
                    temp = turnOrder.GetPlayer()->CallBet(callValue, myDeck);
                    std::cout << "\n\nCallValTest 03     " << callValue << "\n\n";

                    if (turnOrder.GetPlayer()->FoldedHand()) {
                        allCalled.at(betIteration) = true;
                       // std::cout << "\nTest 22\n";
                    }
                    else if (temp > callValue) {
                        callValue = temp;
                        std::cout << "\n\nCallValTest 04     " << callValue << "\n\n";
                       // std::cout << "\nTest 23\n";
                        for (auto i : allCalled) {
                            i = false;
                        }
                        //std::cout << "\nTest 24\n";
                        allCalled.at(betIteration) = true;
                        myPot += turnOrder.GetPlayer()->TakeWager(temp);                //FUNCTION NEEDS DEFINITION
                    }
                    else if (temp == callValue) {
                        //std::cout << "\nTest 25\n";
                        allCalled.at(betIteration) = true;
                        myPot += turnOrder.GetPlayer()->TakeWager(temp);
                        std::cout << "\n\nCallValTest 05     " << callValue << "\n\n";
                    }
                    turnOrder.TraverseNext();
                    //std::cout << "\nTest 26\n";
                }
                else {
                    std::cout << "\n\nCallValTest 06     " << callValue << "\n\n";
                    std::cout << "\n\n\nCPU PLAYER\n\n\n";
                    //std::cout << "\nTest 27\n";
                    CPU* tempPtr = dynamic_cast<CPU*>(turnOrder.GetPlayer());
                    std::vector<PlayerPerception> tempOpinion;              //A vector of opponents opinions of the player's hand/tells
                    std::vector<int> inBluff;                               //A vector of opponents bluff stat - position matched with tempOpinion
                    std::vector<PlayerPerception> tempPerception;           //A vector of opponents opinions of themselves - position matched with the above
                    std::vector<double> inScores;                           //A vector of opponents hand values; used for player decision making if the player
                                                                            //...rolls exceptionally well.  Position matched with the above temp variables
                    for (int iter = 0; iter < PLAYER_COUNT; iter++) {

                        int next = iter + tempBet;
                        if (next >= PLAYER_COUNT) {
                            next -= PLAYER_COUNT;
                      //  std::cout << "\nTest 27\n";
                        }
                       // std::cout << "\nTest 28\n";
                        tempPerception.push_back(playerTells.at(next));
                        tempOpinion.push_back(turnOrder.GetPlayer()->GetPlayerTells(PLAYER_COUNT - iter));          //UNDEFINED
                                                                                                                        //Gets opponent opinion of a specific player's tell

                        inBluff.push_back(turnOrder.GetPlayer()->GetBluffStat());                                   //UNDEFINED
                                                                                                                        //Gets opponent's bluff stat

                        inScores.push_back(turnOrder.GetPlayer()->HandPoints());                                    //DEFINED
                                                                                                      //Gets the actual value of a particular opponents hand
                        turnOrder.TraverseNext();
                        //std::cout << "\nTest 29\n";
                    }
                  //  std::cout << "\nTest 30\n";
                    std::cout << "\n\nCallValTest 07     " << callValue << "\n\n";
                    temp = tempPtr->CallBet(callValue, tempBet + 1, myDeck, tempPerception,
                                                                inScores, inBluff, tempOpinion);
                    std::cout << "\n\nCallValTest 08     " << callValue << "\n\n";
                  //  std::cout << "\nTest 31\n";

                    if (turnOrder.GetPlayer()->FoldedHand()) {
                        allCalled.at(betIteration) = true;
                      //  std::cout << "\nTest 32\n";
                    }
                    else if (temp > callValue) {
                        std::cout << "\n\nCallValTest 09     " << callValue << "\n\n";
                        std::cout << "\nTemp =        " << temp << "\n"
                                  << "\nCallValue =   " << callValue << "\n";
                        callValue = temp - callValue;
                        std::cout << "\nNew Call =    " << callValue << "\n\n";
                        for (auto i : allCalled) {
                            i = false;
                        }
                      //  std::cout << "\nTest 33\n";
                        allCalled.at(betIteration) = true;
                        myPot += turnOrder.GetPlayer()->TakeWager(callValue);
                    std::cout << "\n\nCallValTest 10     " << callValue << "\n\n";
                    }
                    else if (temp == callValue) {
                        std::cout << "\n\nCallValTest 11     " << callValue << "\n\n";
                        allCalled.at(betIteration) = true;
                        myPot += turnOrder.GetPlayer()->TakeWager(callValue);
                        std::cout << "\n\nCallValTest 12     " << callValue << "\n\n";
                    }
                    tempPtr = nullptr;
                    turnOrder.TraverseNext();
                   // std::cout << "\nTest 34\n";
                   std::cout << "\n\nCallValTest 13     " << callValue << "\n\n";
                }
            }
            else {
               // std::cout << "\nTest 35\n";
               std::cout << "\n\nCallValTest 14     " << callValue << "\n\n";
                std::cout << "\nPlayer " << tempBet + 1 << " has folded.\n\n";
                allCalled.at(betIteration) = true;
                turnOrder.TraverseNext();
               // std::cout << "\nTest 36\n";
               std::cout << "\n\nCallValTest 15     " << callValue << "\n\n";
            }
            callingBets = false;
            for (auto i : allCalled) {
                if (i == false) {
                    callingBets = true;
                   // std::cout << "\nTest 37\n";
                }
            }
            std::cout << "\n\nCallValTest 16     " << callValue << "\n\n";
        }
        //std::cout << "\nTest 38\n";
        currBet++;
        std::cout << "\nCurrBet iteration = " << currBet << "\n\n";
        if (currBet >= (PLAYER_COUNT)) {
            currBet -= PLAYER_COUNT;
        }
      //  std::cout << "\nTest 39\n";

        //std::cout << "\nHow much do you bet on this hand?\n\n";

        turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            std::cout << "~~~~~~\nPlayer " << iter + 1 << ":\n\n";
            if (turnOrder.GetPlayer()->FoldedHand()) {
                std::cout << "\nPlayer " << iter + 1 << " has folded\n\n";
                vPlayerScore[iter].points = 0;
            }
            else {
                turnOrder.GetPlayer()->PlayHand();
            }
            turnOrder.TraverseNext();
        }

        double tempMax = 0;
        int tempPos = 0;
        bool tieGame = false;
        turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            if (vPlayerScore[iter].points >= tempMax) {
                tempMax = vPlayerScore[iter].points;
                tempPos = vPlayerScore[iter].playerNum;
                std::cout << "\niter = " << iter << "\n"
                            << "player = " << vPlayerScore[iter].playerNum << "\n"
                            << "points = " << vPlayerScore[iter].points << "\n\n";
                std::cout << "tempMax = " << tempMax << "\n";
            }
        }
        if (!tieGame) {
            std::cout << "Player " << tempPos << " is the winner of the hand!\n\n";
            turnOrder.TraverseStart();
            for (int iter = 1; iter < tempPos; iter++) {
                turnOrder.TraverseNext();
            }
            turnOrder.GetPlayer()->GetCash(myPot);
            myPot = 0;
          //  for (auto i : vPlayerScore) {
           //     std::cout << i.points << "\n";
           // }
            std::cout << "\n";
        }
        else {
            std::cout << "All players tied and get their bets back\n\n";
            turnOrder.TraverseStart();
            for (int iter = 0; iter < PLAYER_COUNT; iter++) {
                int temp = turnOrder.GetPlayer()->GetWager();
                turnOrder.GetPlayer()->GetCash(temp);
                turnOrder.TraverseNext();
            }
            myPot = 0;
        }
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
            //error here if buffer isn't cleared - can skip input and try to find value at a null string??????n

            char choiceAuto = playerChoice.at(0);
            switch(choiceAuto) {
                case 'y' : {
                    for (auto i : playerPtr) {
                        if (!(i->FoldedHand())) {
                            i->DiscardHand(myDeck);
                        }
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
                        if (!(i->FoldedHand())) {
                            i->DiscardHand(myDeck);
                        }
                        delete i;
                    }
                    myDeck.Reshuffle();
                    playerPtr.clear();
                   // std::cout << "\n\nCards in deck = " << myDeck.GetSize() << "\n"
                    //              << "Cards in discard = " << myDeck.DiscardSize() << "\n\n";
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

