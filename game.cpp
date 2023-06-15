#include "game.h"

void Game::FiveCardDraw() {
    bool gameLoop = true;           //Bool that makes sure the game continues to run even after a floor has completed
    Deck myDeck;                    //Stack structure - is both the games stack of cards and the games discard pile
    myDeck.Shuffle();               //Shuffles the deck into a random order

    std::vector<Score> vPlayerScore(PLAYER_COUNT);  //A vector of playerScores - one for each player
    std::vector<Player*> playerPtr(PLAYER_COUNT);   //A vector of player pointers - used to generate circular linked list
    std::vector<PlayerPerception> playerTells(PLAYER_COUNT);
    int currBet = 0;                                //This will be used to rotate the active betting player clockwise each floor
    int betIteration = 0;                           //This will be used to move afloor the table during the rais and call phase of betting
    std::string playerChoice;                       //Used for player input

    NewPlayers(playerPtr, myDeck);

    CircularList<Player*> turnOrder (playerPtr[0]);                                 //Uses the first player to generate the turn order
    GameStart(vPlayerScore, playerPtr, turnOrder);

    while (gameLoop) {
                                                               //The game will continue to run until the loop is broken
        std::vector<float> currPot(PLAYER_COUNT, 0);
        std::vector<std::vector<float>> potVect(1, currPot);
        float myPot = 0;

        for (auto& iter : playerPtr) {
            iter->ResetCurrPot();
        }

        AnteUp(turnOrder, myDeck, myPot, potVect);
        PrintPot(myPot);

        GetTells(turnOrder, playerTells);

        PrintUserHand(turnOrder);

        DiscardCards(turnOrder, playerPtr, vPlayerScore, myDeck, playerTells);

        SetBetLead(currBet, turnOrder);

        float callValue = 0;
        std::vector<bool> allCalled(PLAYER_COUNT, false);
        bool callingBets = true;
        int tempBet = currBet;

        BettingRound(callValue, allCalled, tempBet, myPot, turnOrder,
                     betIteration, callingBets, playerTells, myDeck, potVect);

        CallingRound(myPot, callValue, tempBet, betIteration, turnOrder,
                     allCalled, playerTells, myDeck, callingBets, potVect);

        IncrementCurrBet(currBet, turnOrder);

        PrintAllHands(turnOrder, vPlayerScore);

        CheckWinner(turnOrder, vPlayerScore, myPot, potVect);

        PrintCash(turnOrder);

        PlayAgain(turnOrder, playerPtr, myDeck, gameLoop);
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
}

//******
void Game::PrintPot(float myPot) {
    std::cout << "The pot = " << std::fixed << std::setprecision(2) << "$" << myPot << "\n\n";
}

//******
void Game::AnteUp(CircularList<Player*>& turnOrder, Deck& myDeck, float& myPot, std::vector<std::vector<float>>& potVect) {

    std::cout << "\nThere is a $" << ANTE << " ante for this hand.\n\n";

    turnOrder.TraverseStart();                                                  //Begins the turn order at the beginning
    for (int iter = 0; iter < PLAYER_COUNT; iter++) {                           //Loops until it receives an ante from every player
        float temp = float(turnOrder.GetPlayer()->AnteUp(ANTE, myDeck));                    //Gets the ante from each player
        if (temp < 1) {
            std::cout << "\n\nPlayer " << iter + 1 << " does not have enough money to ante.  They fold.\n\n";
            turnOrder.GetPlayer()->Fold(myDeck);
        }
        myPot += temp;
        int maxPot = potVect.size() - 1;
        potVect[maxPot].at(iter) = temp;
        turnOrder.TraverseNext();                                               //Moves to the next player
    }
}

//******
void Game::NewPlayers(std::vector<Player*>& playerPtr, Deck& myDeck) {
    for (int iter = 0; iter < PLAYER_COUNT; iter++) {           //This loop will generate the players at the table - one physical, and 3 CPU
        if (iter == 0) {
            playerPtr[iter] = new Player(myDeck, 500.00);
        }
        else {
            playerPtr[iter] = new CPU(myDeck, 500.00);
        }
    }
}

//******
void Game::GameStart(std::vector<Score>& vPlayerScore, std::vector<Player*>& playerPtr, CircularList<Player*>& turnOrder) {
    for (int iter = 0; iter < PLAYER_COUNT; iter++) {                           //The player's score is generated based on the value
        vPlayerScore[iter].playerNum = iter + 1;                                //...of the cards in their hand
        vPlayerScore[iter].points = playerPtr[iter]->HandPoints();
    }

    for (int iter = 1; iter < PLAYER_COUNT; iter++) {                           //Fills the turn order object with all players
        turnOrder.NewNode(playerPtr[iter]);
    }

}

//******
void Game::GetTells(CircularList<Player*>& turnOrder, std::vector<PlayerPerception> playerTells) {
    turnOrder.TraverseStart();

    //TELLS TO THE TABLE
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

    //TELLS TO THE PLAYERS
        turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            for (int next = 1; next < PLAYER_COUNT; next++) {
                int temp = iter + next;
                if (temp >= PLAYER_COUNT) {
                    temp -= PLAYER_COUNT;
                }
                turnOrder.GetPlayer()->SetOpinion(playerTells.at(temp));
            }
            turnOrder.TraverseNext();
        }
}

//******
void Game::PrintUserHand(CircularList<Player*>& turnOrder) {
    turnOrder.TraverseStart();
    std::cout << "~~~~~~\nPlayer " << 1 << ":\n\n";
    turnOrder.GetPlayer()->PlayHand(false);
}

//******
void Game::DiscardCards(CircularList<Player*>& turnOrder, std::vector<Player*>& playerPtr,
                  std::vector<Score>& vPlayerScore, Deck& myDeck, std::vector<PlayerPerception>& playerTells) {
    turnOrder.TraverseStart();
    for (int iter = 1; iter < 5; iter++) {
        if (iter == 1) {
            turnOrder.GetPlayer()->DiscardCards(myDeck);
        } else {
            CPU* tempPtr = dynamic_cast<CPU*>(turnOrder.GetPlayer());
            tempPtr->DiscardCards(myDeck);
            tempPtr = nullptr;
        }
        turnOrder.TraverseNext();
    }
    EvaluateCards(vPlayerScore, playerPtr, turnOrder, playerTells);
}

//******
void Game::EvaluateCards(std::vector<Score>& vPlayerScore, std::vector<Player*>& playerPtr,
                   CircularList<Player*>& turnOrder, std::vector<PlayerPerception>& playerTells) {
    turnOrder.TraverseStart();
        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            if (iter == 0) {
                playerTells.at(iter) = AVERAGE;
                std::cout << "\nYou look at your cards.\n\n";
                PrintUserHand(turnOrder);
            } else {
                std::cout << "\nPlayer " << iter + 1 << " looks at their cards...";
                CPU* tempPtr = dynamic_cast<CPU*>(turnOrder.GetPlayer());
                playerTells.at(iter) = tempPtr->JudgeHand();
                tempPtr = nullptr;
            }
            turnOrder.TraverseNext();
        }


        for (int iter = 0; iter < PLAYER_COUNT; iter++) {
            vPlayerScore[iter].points = playerPtr[iter]->HandPoints();        //Evaluates how much each player's hand is worth
        }
}

//******
void Game::SetBetLead(int currBet, CircularList<Player*>& turnOrder) {
    turnOrder.TraverseStart();
    for (int iter = currBet; iter > 0; iter--) {
        turnOrder.TraverseNext();
    }
}

//******
void Game::BettingRound(float& callValue, std::vector<bool>& allCalled, int tempBet, float& myPot,
                  CircularList<Player*>& turnOrder, int& betIteration, bool& callingBets,
                  std::vector<PlayerPerception> playerTells, Deck& myDeck, std::vector<std::vector<float>>& potVect) {

    bool firstBet = true;
    int currPot = 0;
    while (firstBet) {
            int checkFold = 0;
            turnOrder.TraverseNext();
            for (int iter = 0; iter < PLAYER_COUNT - 1; iter++) {
                if (turnOrder.GetPlayer()->FoldedHand()) {
                    checkFold++;
                }
                if (checkFold == PLAYER_COUNT - 1) {
                    callingBets = false;
                    firstBet = false;
                }
                turnOrder.TraverseNext();
            }
            std::cout << "\nPlayer " << tempBet + 1 << " is leading the bet this hand\n";
            PrintPot(myPot);
            if (firstBet) {
                if (tempBet > 0) {
                    CPU* tempPtr = dynamic_cast<CPU*>(turnOrder.GetPlayer());

                    std::vector<PlayerPerception> tempOpinion;              //A vector of opponents opinions of the player's hand/tells
                    std::vector<int> inBluff;                               //A vector of opponents bluff stat - position matched with tempOpinion
                    std::vector<PlayerPerception> tempPerception;           //A vector of opponents opinions of themselves - position matched with the above
                    std::vector<double> inScores;                           //A vector of opponents hand values; used for player decision making if the player
                                                                            //...rolls exceptionally well.  Position matched with the above temp variables

                    for (int iter = 0; iter < PLAYER_COUNT; iter++) {
                        if (iter > 0) {
                            int next = iter + tempBet;
                                if (next >= PLAYER_COUNT) {
                                    next -= PLAYER_COUNT;
                                }
                            tempPerception.push_back(playerTells.at(next));
                            tempOpinion.push_back(turnOrder.GetPlayer()->GetPlayerTells(PLAYER_COUNT - iter));          //UNDEFINED
                                                                                                                        //Gets opponent opinion of a specific player's tell

                            inBluff.push_back(turnOrder.GetPlayer()->GetBluffStat());                                   //UNDEFINED
                                                                                                                        //Gets opponent's bluff stat

                            inScores.push_back(turnOrder.GetPlayer()->HandPoints());                                    //DEFINED
                                                                                                                        //Gets the actual value of a particular opponents hand

                        }
                        turnOrder.TraverseNext();
                    }
                    callValue = tempPtr->BetCash(tempBet + 1, myDeck, tempPerception,
                                                                inScores, inBluff, tempOpinion);
                    allCalled.at(tempBet) = true;
                    tempPtr = nullptr;
                } else {
                    callValue = turnOrder.GetPlayer()->BetCash(myDeck);
                    allCalled.at(tempBet) = true;
                }

            }
            if (turnOrder.GetPlayer()->FoldedHand()) {
                tempBet++;
                if (tempBet >= PLAYER_COUNT) {
                    tempBet = 0;
                }
            }
            else {
                firstBet = false;
            }
            currPot = turnOrder.GetPlayer()->GetCurrPot();
            turnOrder.TraverseNext();
        }

        myPot += callValue;
        potVect[currPot].at(tempBet) += callValue;
        betIteration = tempBet;


}

//******
void Game::PlayerBet() {}

//******
void Game::CPUBet() {}

//******
void Game::CallingRound(float& myPot, float& callValue, int& tempBet, int& betIteration,
                    CircularList<Player*>& turnOrder, std::vector<bool> allCalled,
                    std::vector<PlayerPerception> playerTells, Deck& myDeck,
                    bool& callingBets, std::vector<std::vector<float>>& potVect) {
    while (callingBets) {
        PrintPot(myPot);
        callValue = std::floor(callValue);
        tempBet++;
        if (tempBet >= PLAYER_COUNT) {
            tempBet -= PLAYER_COUNT;
        }
        float temp = 0;
        betIteration++;
        if (betIteration >= PLAYER_COUNT) {
            betIteration -= PLAYER_COUNT;
        }
        if (!(turnOrder.GetPlayer()->FoldedHand())) {
            std::cout << "\nPlayer " << betIteration + 1 << " can choose to call, raise, or fold.\n\n";
            if (betIteration == 0) {
                temp = turnOrder.GetPlayer()->CallBet(callValue, myDeck);
                //std::cout << "\n\nTemp = " << temp << "\n\n";
                if (turnOrder.GetPlayer()->FoldedHand()) {
                    allCalled.at(betIteration) = true;
                } else if (temp > callValue) {
                    callValue = temp;
                    for (auto i : allCalled) {
                        i = false;
                    }
                    allCalled.at(betIteration) = true;
                    int currPot = turnOrder.GetPlayer()->GetCurrPot();
                    myPot += turnOrder.GetPlayer()->SoftWager(callValue);
                    potVect[currPot].at(betIteration) += turnOrder.GetPlayer()->TakeWager(callValue);
                } else if (temp == callValue) {
                    allCalled.at(betIteration) = true;
                    int currPot = turnOrder.GetPlayer()->GetCurrPot();
                    myPot += turnOrder.GetPlayer()->SoftWager(callValue);
                    potVect[currPot].at(betIteration) += turnOrder.GetPlayer()->TakeWager(callValue);
                } else if (temp < callValue && turnOrder.GetPlayer()->CheckCash() == temp) {
                    allCalled.at(betIteration) = true;
                    int currPot = turnOrder.GetPlayer()->GetCurrPot();
                    myPot += turnOrder.GetPlayer()->SoftWager(callValue);
                    potVect[currPot].at(betIteration) += turnOrder.GetPlayer()->AllIn();
                } else if (temp == 0 && turnOrder.GetPlayer()->CheckCash() == 0) {
                    allCalled.at(betIteration) = true;
                }
                turnOrder.TraverseNext();
            } else {
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
                    }
                    tempPerception.push_back(playerTells.at(next));
                    tempOpinion.push_back(turnOrder.GetPlayer()->GetPlayerTells(PLAYER_COUNT - iter));          //UNDEFINED
                                                                                                                    //Gets opponent opinion of a specific player's tell

                    inBluff.push_back(turnOrder.GetPlayer()->GetBluffStat());                                   //UNDEFINED
                                                                                                                        //Gets opponent's bluff stat

                    inScores.push_back(turnOrder.GetPlayer()->HandPoints());                                    //DEFINED
                                                                                                      //Gets the actual value of a particular opponents hand
                    turnOrder.TraverseNext();
                }
                    temp = tempPtr->CallBet(callValue, betIteration + 1, myDeck, tempPerception,
                                                        inScores, inBluff, tempOpinion);
                    //std::cout << "\n\nTemp = " << temp << "\n\n";

                if (turnOrder.GetPlayer()->FoldedHand()) {
                    allCalled.at(betIteration) = true;
                } else if (temp > callValue && turnOrder.GetPlayer()->CheckCash() > 0) {
                    callValue = temp;
                    for (auto i : allCalled) {
                        i = false;
                    }
                    allCalled.at(betIteration) = true;
                    int currPot = turnOrder.GetPlayer()->GetCurrPot();
                    myPot += turnOrder.GetPlayer()->SoftWager(callValue);
                    potVect[currPot].at(betIteration) += turnOrder.GetPlayer()->TakeWager(callValue);
                } else if (temp == callValue) {
                    allCalled.at(betIteration) = true;
                    int currPot = turnOrder.GetPlayer()->GetCurrPot();
                    myPot += turnOrder.GetPlayer()->SoftWager(callValue);
                    potVect[currPot].at(betIteration) += turnOrder.GetPlayer()->TakeWager(callValue);
                }else if (temp < callValue && turnOrder.GetPlayer()->CheckCash() == temp) {
                    allCalled.at(betIteration) = true;
                    int currPot = turnOrder.GetPlayer()->GetCurrPot();
                    myPot += turnOrder.GetPlayer()->SoftWager(callValue);
                    potVect[currPot].at(betIteration) += turnOrder.GetPlayer()->AllIn();
                } else if (temp == 0 && turnOrder.GetPlayer()->CheckCash() == 0) {
                    allCalled.at(betIteration) = true;
                }
                tempPtr = nullptr;
                turnOrder.TraverseNext();
            }
        } else {
            std::cout << "\nPlayer " << betIteration + 1 << " has folded.\n\n";
            allCalled.at(betIteration) = true;
            turnOrder.TraverseNext();
        }
        callingBets = false;
        for (auto i : allCalled) {
            if (i == false) {
                callingBets = true;
            }
        }
    }

    DistributePot(potVect, turnOrder);
}

//******
void Game::PlayerCall() {}

//******
void Game::CPUCall() {}

//******
void Game::IncrementCurrBet(int& currBet, CircularList<Player*>& turnOrder) {
    //std::cout << "\nTest 38\n";
    currBet++;
        //std::cout << "\nCurrBet iteration = " << currBet << "\n\n";
    if (currBet >= (PLAYER_COUNT)) {
        currBet -= PLAYER_COUNT;
    }
    //  std::cout << "\nTest 39\n";
    //std::cout << "\nHow much do you bet on this hand?\n\n";

    turnOrder.TraverseStart();
}

//******
void Game::PrintAllHands(CircularList<Player*>& turnOrder, std::vector<Score>& vPlayerScore) {
    for (int iter = 0; iter < PLAYER_COUNT; iter++) {
        std::cout << "~~~~~~\nPlayer " << iter + 1 << ":\n\n";
        if (turnOrder.GetPlayer()->FoldedHand()) {
            std::cout << "\nPlayer " << iter + 1 << " has folded\n\n";
            vPlayerScore[iter].points = 0;
        }
        else {
            turnOrder.GetPlayer()->PlayHand(false);
        }
        turnOrder.TraverseNext();
    }
}

//******
void Game::CheckWinner(CircularList<Player*>& turnOrder, std::vector<Score> vPlayerScore,
                        float& myPot, std::vector<std::vector<float>>& potVect) {
    double tempMax = 0;
    int tempPos = 0;
    bool tieGame = false;
    for (int iter = 0; iter < potVect.size(); iter++) {
    turnOrder.TraverseStart();
        double tempMax = 0;
        int tempPos = 0;
        for (int next = 0; next < PLAYER_COUNT; next++) {
            if (vPlayerScore[next].points >= tempMax && turnOrder.GetPlayer()->GetCurrPot() >= iter) {
                tempMax = vPlayerScore[next].points;
                tempPos = vPlayerScore[next].playerNum;
            }
            turnOrder.TraverseNext();
        }
        std::cout << "Player " << tempPos << " is the winner of pot " << iter + 1 << "!\n\n";
        turnOrder.TraverseStart();
        for (int next = 1; next < tempPos; next++) {
            turnOrder.TraverseNext();
        }
        for (int next = 0; next < PLAYER_COUNT; next++) {
            turnOrder.GetPlayer()->GetCash(potVect[iter].at(next));
            //std::cout << potVect[iter].at(next) << "\n\n";
        }
    }
}

//******
void Game::PrintCash(CircularList<Player*>& turnOrder) {
    turnOrder.TraverseStart();
    for (int iter = 0; iter < PLAYER_COUNT; iter++) {
        std::cout << "Player " << iter + 1 << " has $" << turnOrder.GetPlayer()->CheckCash() << "\n";
        turnOrder.TraverseNext();
    }
    std::cout << "\n";
}

//******
void Game::PlayAgain(CircularList<Player*>& turnOrder, std::vector<Player*>& playerPtr, Deck& myDeck, bool& gameLoop) {
    turnOrder.TraverseStart();
    std::string playerChoice = "";
    bool choiceLoop = true;
   // std::cout << "\n\nDeck size: " << myDeck.GetSize() << "\n"
     //           << "\nDiscard size: " << myDeck.DiscardSize() << "\n\n";
    while (choiceLoop) {
        std::cout << "\n\nWould you like to play again?\n"
                  << "Type <yes> to play again, or <no> to quit\n\n";
        std::cin >> playerChoice;
        //error here if buffer isn't cleared - can skip input and try to find value at a null string??????n
        char choiceAuto = 'p';
        if (playerChoice.size() > 0) {
            choiceAuto = tolower(playerChoice.at(0));
        }
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
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                break;
            }
        }
    }
    playerChoice = "";
}

void Game::DistributePot(std::vector<std::vector<float>>& myPot, CircularList<Player*>& turnOrder) {
    turnOrder.TraverseStart();
    float largestValue = 0;
    float smallestValue = 0;
    for (int iter = 0; iter < myPot.size(); iter++) {
        for (int next = 0; next < PLAYER_COUNT; next++) {
            float temp = myPot[iter].at(next);
            if (temp > largestValue) {
                largestValue = temp;
            }
            turnOrder.TraverseNext();
        }
        smallestValue = largestValue;
        for (int next = 0; next < PLAYER_COUNT; next++) {
            float temp = myPot[iter].at(next);
            if (temp < smallestValue && temp > 0) {
                smallestValue = temp;
            }
            turnOrder.TraverseNext();
        }
        turnOrder.TraverseStart();
        for (int next = 0; next < PLAYER_COUNT; next++) {
            if (myPot[iter].at(next) > smallestValue) {
                int temp = myPot[iter].at(next) - smallestValue;
                if (myPot.size() == iter + 1) {
                    std::vector<float> tempVect(PLAYER_COUNT, 0);
                    tempVect.at(next) = temp;
                    myPot.push_back(tempVect);
                } else {
                    myPot[iter + 1].at(next) = temp;
                }
                turnOrder.GetPlayer()->IncrementPot();
            }
            turnOrder.TraverseNext();
        }
        if (myPot.size() > iter + 1) {
            for (int next = 0; next < PLAYER_COUNT; next++) {
                myPot[iter].at(next) = smallestValue;
            }
        }
        //std::cin >> tempin;
    }
}

