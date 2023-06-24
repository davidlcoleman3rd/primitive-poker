//***********************************************
//      HAND CLASS                              *
//                                              *
//***********************************************
//                                              *
//  This C++ class serves as a vector structure *
//  of card objects.  This is the main source   *
//  card objects that players will use as       *
//  their "hands" when playing the game.        *
//                                              *
//***********************************************
//  Version 0.0.4.1 pushed by David Coleman III *
//  on  01 - 24 - 23                            *
//***********************************************

//***********************************************

#include "hand.h"

//***********************************************

    Hand::Hand(int handSize, Deck& dInput) {
        GetHand(handSize, dInput);
    }

//******
    void Hand::GetHand(int handSize, Deck& dInput) {        //Generates a hand of cards for the player
        DrawCard(handSize, dInput);
    }

//******
    void Hand::SortHand() {                                 //Sorts the cards based on value - Aces first, Twos last

        std::vector<Card> vTempSort;                                //Temporary vector used for sorting
        int iSize = vCards.size();                                  //Size of the hand to be sorted
        Card* tempPtr = nullptr;                                   //Pointer that serves to temporarily refer to a card

        for (int iCount = 0; iCount < iSize; iCount++) {            //Iterates over the entire hand of cards
            int vCardSize = vCards.size();                              //Stores vCard's size - holds it as a prev value
            for (int iter = 0; iter < vCardSize; iter++) {              //Iterates using the "previous" card size
                CardNum cnFinal;                                            //The largest card value found in the hand
                CardNum cnTemp;                                             //The current card value being tested
                cnTemp = vCards.at(iter).GetNum();                          //Gets the current card value at the iteration location
                Card cardTemp(vCards.at(iter));                             //Creates a local card variable by using cardTemp to copy the card at the location
                if (cnTemp > cnFinal || iter == 0) {                        //If temp is greater than final or the iteration is beginning...
                    if (tempPtr != nullptr) {                                  //If tempCard is not pointing at null...
                        delete tempPtr;                                            //Delete and empty tempCard
                        tempPtr = nullptr;
                    }
                    cnFinal = cnTemp;                                           //Set the final value to the current value
                    tempPtr =  new Card(cardTemp);                              //Dynamically allocate a copy of current cardTemp
                }
            }
            vTempSort.push_back(*(tempPtr));                                //Store the card's qualities as an element of the sorting vector
            for (int iter = 0; iter < int(vCards.size()); iter++) {         //Iterate over vCards
                if (vCards.at(iter) == *(tempPtr)) {                           //When the card to be copied is found, it is erased from the vector.
                    vCards.erase(vCards.begin() + iter);
                }
            }
            delete tempPtr;                                             //The pointer is free'd and no longer dangling
            tempPtr = nullptr;
        }
        vCards = vTempSort;                                         //Copies the sorted vector directly over the hand vector - stores the sorted hand into the player's hand
    }

//******
    void Hand::DrawCard(int iCount, Deck& dInput) {                   //Draws cards for the player - draws based on iCount, where iCount is the number of cards the player should draw
        for (int iter = 0; iter < iCount; iter++) {                 //Pushes back a number of cards equal to the draw amount into the player's hand
            vCards.push_back(dInput.DealCard(HAND_STATE));
        }
    }

//******
    void Hand::PrintHand() const {                                  //Print's the player's entire hand of cards.
        std::cout << "Player hand:\n\n";
        for (auto& iter : vCards) {
            std::cout << " ,,,,,,, ";
        }
        std::cout << "\n";


        for (auto& iter : vCards) {
            std::cout << " |" << iter.GetSuitSym() << "  " << iter.GetNumStr() << "| ";
        }
        std::cout << "\n";

        for (auto& iter : vCards) {
            std::cout << " |     | ";
        }
        std::cout << "\n";

        for (auto& iter : vCards) {
            std::cout << " |" << iter.GetSuitStr() << "| ";
        }
        std::cout << "\n";

        for (auto& iter : vCards) {
            std::cout << " |     | ";
        }
        std::cout << "\n";

        for (auto& iter : vCards) {
            std::cout << " |" << iter.GetNumStr() << "  " << iter.GetSuitSym() << "| ";
        }
        std::cout << "\n";

         for (auto& iter : vCards) {
            std::cout << " ``````` ";
        }
        std::cout << "\n";
    }

//******
    //******
    void Hand::PrintCard(Card cardin) const {           //Prints a single selected card
        std::cout << " ,,,,,,, ";
        std::cout << "\n";


        std::cout << " |" << cardin.GetSuitSym() << "  " << cardin.GetNumStr() << "| ";
        std::cout << "\n";
        std::cout << " |     | ";
        std::cout << "\n";

        std::cout << " |" << cardin.GetSuitStr() << "| ";
        std::cout << "\n";

        std::cout << " |     | ";
        std::cout << "\n";

        std::cout << " |" << cardin.GetNumStr() << "  " << cardin.GetSuitSym() << "| ";
        std::cout << "\n";

        std::cout << " ``````` ";
        std::cout << "\n";
    }


//******
 void Hand::PrintAces() const {                                  //Print's all aces in the player's hand
        std::cout << "Player hand:\n\n";
        for (auto& iter : vCards) {
            if (iter.GetNum() == ACE)
                std::cout << " ,,,,,,, ";
        }
        std::cout << "\n";


        for (auto& iter : vCards) {
            if (iter.GetNum() == ACE)
                std::cout << " |" << iter.GetSuitSym() << "  " << iter.GetNumStr() << "| ";
        }
        std::cout << "\n";

        for (auto& iter : vCards) {
            if (iter.GetNum() == ACE)
                std::cout << " |     | ";
        }
        std::cout << "\n";

        for (auto& iter : vCards) {
            if (iter.GetNum() == ACE)
                std::cout << " |" << iter.GetSuitStr() << "| ";
        }
        std::cout << "\n";

        for (auto& iter : vCards) {
            if (iter.GetNum() == ACE)
                std::cout << " |     | ";
        }
        std::cout << "\n";

        for (auto& iter : vCards) {
            if (iter.GetNum() == ACE)
                std::cout << " |" << iter.GetNumStr() << "  " << iter.GetSuitSym() << "| ";
        }
        std::cout << "\n";

         for (auto& iter : vCards) {
            if (iter.GetNum() == ACE)
                std::cout << " ``````` ";
        }
        std::cout << "\n";
    }


//******
    double Hand::CountPoints(bool print) {
        SortHand();
        long double totalScore = 0;
        int outputScore = 0;
        int iteration = 0;
        CardSuit csTemp;
        CardNum cnTemp;


        for (auto& iter : vCards) {
            //            13 ^ -x, where x is 13 - the value of the card + 1; This means ACE will return 1.0, whereas 2 will return 4E-14, etc
            //
            //              TWO     -   13 ^ -(13 - 1)  =   4^-14
            //              THREE   -   13 ^ -(13 - 2)  =   5^-13
            //              FOUR    -   13 ^ -(13 - 3)  =   7^-12
            //              FIVE    -   13 ^ -(13 - 4)  =   9^-11
            //              SIX     -   13 ^ -(13 - 5)  =   1^-9
            //              SEVEN   -   13 ^ -(13 - 6)  =   1^-8
            //              EIGHT   -   13 ^ -(13 - 7)  =   2^-7
            //              NINE    -   13 ^ -(13 - 8)  =   2^-6
            //              TEN     -   13 ^ -(13 - 9)  =   3^-5
            //              JACK    -   13 ^ -(13 - 10) =   4^-4
            //              QUEEN   -   13 ^ -(13 - 11) =   5^-3
            //              KING    -   13 ^ -(13 - 12) =   7^-2
            //              ACE     -   13 ^ -(13 - 13) =   1
            //
            totalScore += double(1 / std::pow(13,(13 - (int(iter.GetNum()) + 1))));
        }

        int streak = 0;
        bool hasOneAce = false;                 //Logic bools - each checks for a certain "condition" with the hand, which is used for scoring.
        bool multiAce = false;                  //          /
        bool hasPair = false;                   //         /
        bool hasTrips = false;                  //        /
        bool hasQuads = false;                  //       /
        bool twoPair = false;                   //      /
        bool fullHouse = false;                 //  <--/
        bool tripsFirst = false;                // Checks to see if the "three of a kind" comes before a "pair" in a "Full House" - scoring is handled differently depending on which comes first
        std::vector<int> StreakedCards;
        for (auto& iter : vCards) {                                     //Iterates over the player's hand for scoring

            if (iter.GetNum() == ACE) {                                     //Logic to determine if the player has exactly one ace
                if (hasOneAce && !multiAce) {                               //This is used in instances where a player has a "straight" consisting of A-2-3-4-5
                    hasOneAce = false;
                    multiAce = true;
                } else if (!hasOneAce && !multiAce){
                    hasOneAce = true;
                }
            }

            //This block is used for checking if a player has any "matches" - pair, two pair, toak, foak, and full house
            //Cards are organized by "streaks" - Cards stored in the "streaked" vector can be used for "matched" hands
            //Streak is iterated to test for the proper hand

            if (iteration > 0) {
                if (cnTemp == iter.GetNum()) {                              //If the current card is equal to the previous card...

                    if (hasPair && streak == 1 && !twoPair) {                   //Three of a kind block
                        hasTrips = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else if (hasTrips && streak == 2) {                         //Four of a kind block
                        hasQuads = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else if (hasTrips && streak == 0) {                         //Full house (trips first) block
                        fullHouse = true;
                        tripsFirst = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        hasPair = true;
                        streak++;
                    }
                    else if (hasPair && streak == 0) {                          //Two pair block
                        twoPair = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else if (twoPair) {                                         //Full house (pair first) block
                        hasTrips = true;
                        hasPair = true;
                        fullHouse = true;
                        twoPair = false;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else {                                                      //Pair block
                        hasPair = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                }
                else {                                                      //If it's the player's first card or it doesn't match the previous card, the streak is reset
                                                                            //This is important for making sure streaks are monitored properly, so the game doesn't think
                    streak = 0;                                             //we have a four of a kind when we have a full house
                }
            }
            cnTemp = iter.GetNum();
            iteration++;
        }
        unsigned long int temp = 0;                                         //Variable to hold the player's final "score" - the grading of their hand
                                                                            //Using the table above and the 1-13 value of each card, superior hands will always win
                                                                            //  An unsigned long int was used as a precaution - extremely long decimal points as well as
                                                                            //  very large values must both be used to assure that superior hands ALWAYS beat weaker hands


        //This block will take the logic bools and use them to store the player's score and return it, as well as output that player's hand
        //...should the bool for outputting be set to true

        if (hasPair) {                                              //If the player has a pair...
            if (hasTrips) {                                             //If the player has a three of a kind...
                if (hasQuads) {                                             //4 of a kind block
                    for (auto iter : StreakedCards) {
                        int holdCard = iter;
                        temp += (holdCard * QUADS_MULT);
                    }
                    outputScore = QUADS_OUT;
                }
                else if (fullHouse) {                                       //Full house block
                    if (tripsFirst) {                                           //3 of a kind first...
                        for (int iter = 0; iter < 3; iter++) {
                            int holdCard = StreakedCards.at(iter);
                            temp += (holdCard * FULLHOUSE_TRIPS_MULT);
                        }
                        for (int iter = 3; iter < 5; iter++) {
                            int holdCard = StreakedCards.at(iter);
                            temp += (holdCard * FULLHOUSE_PAIR_MULT);
                        }
                    }
                    else {                                                      //Pair first...
                        for (int iter = 0; iter < 2; iter++) {
                            int holdCard = StreakedCards.at(iter);
                            temp += (holdCard * FULLHOUSE_PAIR_MULT);
                        }
                        for (int iter = 2; iter < 5; iter++) {
                            int holdCard = StreakedCards.at(iter);
                            temp += (holdCard * FULLHOUSE_TRIPS_MULT);
                        }
                    }
                    outputScore += FULLHOUSE_OUT;
                }
                else {                                                      //3 of a kind block
                    for (auto iter : StreakedCards) {
                        int holdCard = iter;
                        temp += (holdCard * TRIPS_MULT);
                    }
                    outputScore += TRIPS_OUT;
                }
            }
            else if (twoPair) {                                         //Two pair block
                for (int iter = 0; iter < 2; iter++) {
                    int holdCard = StreakedCards.at(iter);
                    temp += (holdCard * TWOPAIR_MULT);
                }
                for (int iter = 2; iter < 4; iter++) {
                    int holdCard = StreakedCards.at(iter);
                }
                outputScore += TWOPAIR_OUT;
            }
            else {                                                      //pair block
                for (auto iter : StreakedCards) {
                    int holdCard = iter;
                    temp += (holdCard);
                }
                outputScore += PAIR_OUT;
            }
            totalScore += double(temp);
            if (print)
                ShowScore(outputScore, totalScore);
            return totalScore;
        }


//If no matched hands can be found, the function will then search for any possible straights or flushes, return the value, and print the score if the bool is true.

        bool isStraight = true;                                                     //Logic bools for straight and flush - flip to false if a condition isn't met
        bool isFlush = true;
        iteration = 0;                                                              //Simply checks to see if checking the first card - if so, don't set to false
        for (auto iter : vCards) {
            if (iteration > 0) {
                if (iter.GetSuit() != csTemp) {                                         //If the current suit doesn't match the previous suit, not a flush
                    isFlush = false;
                }
                if (iter.GetNum() != (cnTemp - CardNum(1)) || multiAce) {               //If the curr value is not exactly one less than prev OR you have multiple aces, not straight
                    isStraight = false;
                } else if (iter.GetNum() != (cnTemp - CardNum(1)) && hasOneAce) {      //If the same, except you have one ace and it is not the prev value while the next is 5, not straight
                    if (!(cnTemp == ACE && iter.GetNum() == FIVE)) {
                        isStraight = false;
                    }
                }
            }
            StreakedCards.push_back(int(iter.GetNum()) + 1);                        //Pushes back the cards parsed for straight and flushness into a new vector; streakedCards
            csTemp = iter.GetSuit();                                                //Stores the previous suit and value for parsing purposes
            cnTemp = iter.GetNum();
            iteration++;                                                            //Iterates
        }


//This block will check the straightness and flushness of the hand - it will then output if required and return the score to the calling function

        if (isStraight) {                                       //Straight block...
            if (isFlush) {                                          //Straight flush block...
                for (auto iter : StreakedCards) {
                    int holdCards = iter;
                    temp += (holdCards * STRAIGHTFLUSH_MULT);
                }
                outputScore += STRAIGHT_OUT;
                if (temp > ROYAL_THRESHOLD) {                       //Royal flush block...
                    totalScore = ROYAL_MULT;
                    outputScore = ROYAL_OUT;
                    ShowScore(outputScore, totalScore);
                    return totalScore;
                }
                outputScore += FLUSH_OUT;

            } else {
                for (auto iter : StreakedCards) {
                    int holdCards = iter;
                    temp += (holdCards * STRAIGHT_MULT);
                }
                outputScore += STRAIGHT_OUT;
            }
            totalScore += double(temp);
        } else if (isFlush) {                                       //Flush block....
            for (auto iter : StreakedCards) {
                int holdCards = iter;
                temp += (holdCards * FLUSH_MULT);
                totalScore += double(temp);
            }
            outputScore += FLUSH_OUT;
        }
        if (print)
            ShowScore(outputScore, totalScore);                     //Output if necessary
        return totalScore;                                          //return score to the calling function
    }

//******
    int Hand::CardCount() {                             //Returns the size of the player's hand to the calling function
        return vCards.size();
    }

//******
    void Hand::DiscardCards(Deck& dInput) {             //Allows the user player to select and discard cards from their hand
        int discardCount = 0;
        int discardChoice = 0;
        bool hasAce = false;
        std::vector<Card> tempVect;
        Card* tempCard = nullptr;

        for (auto i : vCards) {
            if (i.GetNum() == ACE) {
                hasAce = true;
            }
        }

        if (hasAce) {
            for (auto i : vCards) {
                if (i.GetNum() == ACE) {
                    tempVect.push_back(i);
                }
            }
        }

        while (discardCount < 1 || discardCount > 5) {
            std::cout << "How many cards would you like to discard?\n\n";
            std::cin >> discardCount;
            if (discardCount == 0 && std::cin) {
                return;
            } else if (discardCount == 4) {
                if (!hasAce) {
                    discardCount = 0;
                    std::cout << "\nCannot discard 4 - no aces\n";
                }
            } else if (discardCount > 4 || discardCount < 1 || !std::cin) {
                discardCount = 0;
                std::cout << "\nInvalid entry - enter a number between 1 and 3, or up to 4 if you have an ace\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }
        if (hasAce) {
            int keepChoice = 0;
            if (tempVect.size() > 1) {
                PrintAces();
                while (keepChoice < 1 || keepChoice >= tempVect.size()) {
                    std::cout << "\nChoose which ace keep\n\n";
                    std::cin >> keepChoice;
                    if (!std::cin) {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cout << "\n\nInvalid entry.  Please try again.\n";
                    }
                    tempCard = &(tempVect.at(keepChoice - 1);
                }
            } else {
                tempCard = &(tempVect.at(0));
            }

        }
        if (discardCount == 4) {
            for (int iter = vCards.size(); iter > 1; iter--) {
                dInput.ToDiscard(vCards.at(iter - 1));
                vCards.erase(vCards.begin() + (iter - 1));
            }
        } else {
            for (int iter = 0; iter < discardCount; iter++) {
                discardChoice = -1;
                bool cancelEarly = false;
                int handSize = vCards.size();
                while ((discardChoice < 1 || discardChoice > handSize) && !cancelEarly) {
                    PrintHand();
                    std::cout << "\nChoose card #" << iter + 1 << " to discard.\n"
                              << "Enter 0 to stop discarding cards\n\n";
                    std::cin >> discardChoice;
                    if (discardChoice == 0 && std::cin) {
                        discardCount = iter;
                        cancelEarly = true;
                        iter = discardCount;
                    } else if (discardChoice < 1 || discardChoice > handSize || !std::cin) {
                        discardChoice = -1;
                        std::cout << "\nInvalid entry - enter a number between 1 and " << vCards.size() << "\n";
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                    } else if (hasAce) {
                        if (*(tempCard) == vCards.at(discardChoice - 1) && discardCount == 4) {
                            std::cout << "\nCan't discard your shown ace when discarding 4 cards\n\n";
                            discardChoice = -1;
                        }
                    }
                }
                if (!cancelEarly) {
                    dInput.ToDiscard(vCards.at(discardChoice - 1));
                    vCards.erase(vCards.begin() + (discardChoice - 1));
//                  vCards.resize(discardChoice - 1);
                    std::cout << "\n\n";
                    discardChoice = -1;
                }
            }
        }
        DrawCard(discardCount, dInput);
        SortHand();
//      PrintHand();
    }

//******
    void Hand::DiscardHand(Deck& dInput) {
        for (auto i : vCards) {
            dInput.ToDiscard(i);
        }
        for (int iter = vCards.size(); iter > 0; iter--) {
            vCards.erase(vCards.begin() + (iter - 1));
//          vCards.resize(iter - 1);
        }
        vCards.clear();
    }

//******
    void Hand::SelectCards(std::vector<int>& selections) {              //Will pass back a vector of the cards the CPU would want to discard
        Card* prevCard = nullptr;                                       //The last card analyzed by the player - Free
        std::vector<Card*> goodCards;                                   //Cards that the player will keep - Free
        std::vector<Card*> badCards;                                    //Cards that the player will throw away - Free
        std::vector<Card*> straightCheck;                               //A copy of bad cards - this will be used for the player to determine if they're nearing a straight - Free
        std::vector<Card*> flushCheck;                                  //A copy of bad cards - this will be used for the player to determine if they're nearing a flush - Free
        bool streak = false;                                            //State check to see if the player is currently on a streak of like cards
        bool hasAce = false;                                            //State check to see if the player has an ace
        int nearStraight = 0;                                           //Checks to see how close the player is to having a straight
        int nearFlush = 0;                                              //Checks to see how close the player is to having a flush
        int discardCount = 0;                                           //The number of cards the player would discard in this instance


        std::vector<std::vector<Card*>> straightCards;                  //Free
        std::vector<std::vector<Card*>> flushCards;                     //Free

        for (int iter = 0; iter < vCards.size(); iter++) {
            //std::cout << "\n\nTest 01\n\n";
            Card* i = &vCards.at(iter);
            if (i->GetNum() == ACE) {
                hasAce = true;
            }
            if (prevCard == nullptr) {
                prevCard = i;
              //  std::cout << "\n\nTest 02\n\n";
            }
            else {
                //std::cout << "\ni    = " << i->GetNum()
                  //            << "\nprev = " << prevCard->GetNum()
                    //          << "\ni suit   = " << i->GetSuit()
                      //        << "\nprevSuit = " << prevCard->GetSuit()
                        //      << "\n\n\n";
                if (i->GetNum() == prevCard->GetNum()) {

                    if (streak) {
                        goodCards.push_back(i);
                    }
                    else {
                        streak = true;
                        goodCards.push_back(prevCard);
                        goodCards.push_back(i);
                    }
                //std::cout << "\n\nTest 03\n\n";
                }
                else {
                    if (!(streak)) {
                        badCards.push_back(prevCard);
                        straightCheck.push_back(prevCard);
                        flushCheck.push_back(prevCard);
                    }
                    else {
                        streak = false;
                    }
                    if (i->GetSuit() == vCards.back().GetSuit() && i->GetNum() == vCards.back().GetNum()) {
                        badCards.push_back(i);
                        straightCheck.push_back(i);
                        flushCheck.push_back(i);
                    }
                  //  std::cout << "\n\nTest 04\n\n";
                }
            }
            prevCard = i;
            i = nullptr;                                                                                    //i free'd appropriately
        }


        //std::cout << "\n\nTest 05\n\n";
                                                                                                            //NEED TO REANLYZE ALL OF THIS - THE WRONG VALUES ARE BEING SELECTED WHEN SORTING THROUGH THE VECTORS
                                                                                                            //!!!!!!!!!!!!!!!!!!!!
                                                                                                            //!!!!!!!!!!!!!!!!!!!!
                                                                                                            //!!!!!!!!!!!!!!!!!!!!
        if (goodCards.size() == 0) {
          //  std::cout << "\n\nTest 06\n\n";
            while (straightCheck.size() > 0) {
            //    std::cout << "\n\nStraightCheck size = " << straightCheck.size() << "\n\n";
              //  std::cout << "\n\nTest 07\n\n";
                std::vector<int> tempNums;
                CardNum tempNum;
                for (int iter = 0; iter < straightCheck.size(); iter++) {
                //    std::cout << "\n\nTest 08\n\n";
                    if (iter == 0) {
                  //      std::cout << "\n\nTest 41, iter " << iter << "\n\n";
                        tempNum = straightCheck.at(iter)->GetNum();
                    //    std::cout << "\n\nTest 42, iter " << iter << "\n\n";
                        tempNums.push_back(iter);
                      //  std::cout << "\n\nTest 43, iter " << iter << "\n\n";
                    }
                    else {
                        //std::cout << "\n\nTest 09\n\n";
                        if (straightCheck.at(iter)->GetNum() < tempNum && straightCheck.at(iter)->GetNum() > tempNum - 5) {
                          //  std::cout << "\n\nTest 44, iter " << iter << "\n\n";
                            tempNums.push_back(iter);
                        }
                    }
                }
                std::vector<Card*> tempVect;
                for (auto i : tempNums) {
                    //std::cout << "\n\nTest 10\n\n";
                    tempVect.push_back(straightCheck.at(i));
                }
                int rangeCount = 0;
                for (auto i : tempNums) {
                    i -= rangeCount;
                   // std::cout << "\n\nTest 11\n\n";
                  //  std::cout << "i = " << i << "\n\n";                                     //NEED TO REANALYZE
                    //std::cout << "straightCheck = " << straightCheck.size() << "\n\n";
                    straightCheck.at(i) = nullptr;
                    straightCheck.erase(straightCheck.begin() - i);
                    rangeCount++;
                }
                //std::cout << "\n\nTest 40\n\n";
                straightCards.push_back(tempVect);
                tempVect.clear();
                //std::cout << "\n\nTest 12\n\n";
            }
            //std::cout << "\n\nTest 13\n\n";
            while (flushCheck.size() > 0) {
              //  std::cout << "\n\nTest 14\n\n";
                std::vector<int> tempNums;
                CardSuit tempSuit;
                for (int iter = 0; iter < flushCheck.size(); iter++) {
                //    std::cout << "\n\nTest 15\n\n";
                    if (iter == 0) {
                  //      std::cout << "\n\nTest 16\n\n";
                        tempSuit = flushCheck.at(iter)->GetSuit();
                        tempNums.push_back(iter);
                    }
                    else {
                    //    std::cout << "\n\nTest 17\n\n";
                        if (tempSuit == flushCheck.at(iter)->GetSuit()) {
                            tempNums.push_back(iter);
                        }
                    }
                }
                //std::cout << "\n\nTest 18\n\n";
                std::vector<Card*> tempVect;
                for (auto i : tempNums) {
                  //  std::cout << "\n\nTest 19\n\n";
                    tempVect.push_back(flushCheck.at(i));
                }
                int rangeCheck = 0;
                for (auto i : tempNums) {
                    i -= rangeCheck;
                    //std::cout << "\n\nTest 20\n\n";
                    flushCheck.at(i) = nullptr;
                    flushCheck.erase(flushCheck.begin() + i);
                    rangeCheck++;
                }
                flushCards.push_back(tempVect);
                //std::cout << "\n\nTest 21\n\n";
                for (auto i : tempVect) {
                    i = nullptr;
                }
                 //std::cout << "\n\nTest 22\n\n";
                tempVect.clear();                                                   //Tempvect free'd appropriately
                //std::cout << "\n\nTest 23\n\n";
            }
            int flushNum = 0;
            int straightNum = 0;
            for (auto i : flushCards) {
                if (i.size() > flushNum) {
                    flushNum = i.size();
                }
            }
             //std::cout << "\n\nTest 24\n\n";

            for (auto i : straightCards) {
                if (i.size() > straightNum) {
                    straightNum = i.size();
                }
            }
             //std::cout << "\n\nTest 25\n\n";

            int biggestNum = 0;
            int biggestVect = 0;
             //std::cout << "\n\nTest 26\n\n";
            badCards.clear();
             //std::cout << "\n\nTest 27\n\n";
            if (flushNum >= straightNum) {
                //std::cout << "\n\nTest 28\n\n";
                for (int iter = 0; iter < flushCards.size(); iter++) {
                    if (flushCards.at(iter).size() > biggestNum) {
                        biggestNum = flushCards.at(iter).size();
                        biggestVect = iter;
                    }
                }
                //std::cout << "\n\nTest 29\n\n";

                for (int iter = 0; iter < flushCards.size(); iter++) {
                    if (iter == biggestVect) {
                        for (auto i : flushCards.at(iter)) {
                            goodCards.push_back(i);
                        }
                    }
                    else {
                        for (auto i : flushCards.at(iter)) {
                            badCards.push_back(i);
                        }
                    }
                }
                //std::cout << "\n\nTest 30\n\n";
            }
            else {
                //std::cout << "\n\nTest 31\n\n";
                for (int iter = 0; iter < straightCards.size(); iter++) {
                    if (straightCards.at(iter).size() > biggestNum) {
                        biggestNum = straightCards.at(iter).size();
                        biggestVect = iter;
                    }
                }
                //std::cout << "\n\nTest 32\n\n";

                for (int iter = 0; iter < straightCards.size(); iter++) {
                    if (iter == biggestVect) {
                        for (auto i : straightCards.at(iter)) {
                            goodCards.push_back(i);
                        }
                    }
                    else {
                        for (auto i : straightCards.at(iter)) {
                            badCards.push_back(i);
                        }
                    }
                }
                //std::cout << "\n\nTest 33\n\n";
            }
        }

        //**
        //std::cout << "\n\nTest 34\n\n";
        if (badCards.size() >= 3) {
            if (hasAce) {
                discardCount = 4;
            }
            else {
                discardCount = 3;
            }
          //  std::cout << "\n\nTest 35\n\n";
        }
        else {
            discardCount = badCards.size();
            //std::cout << "\n\nTest 36\n\n";

        }

        for (int iter = 0; iter < vCards.size(); iter++) {
            for (auto k : badCards) {
                if ((k->GetNum() == vCards.at(iter).GetNum()) && (k->GetSuit() == vCards.at(iter).GetSuit())) {
                    selections.push_back(iter);
                }
            }
        }
        //std::cout << "\n\nTest 37\n\n";

        prevCard = nullptr;                         //PrevCard free'd appropriately
        for (auto i : badCards) {                   //BadCards free'd appropriately
            i = nullptr;
        }
        badCards.clear();
        for (auto i : goodCards) {                  //GoodCards free'd appropriately
            i = nullptr;
        }
        goodCards.clear();
        for (auto i : straightCheck) {              //StraightCheck free'd appropriately
            i = nullptr;
        }
        straightCheck.clear();
        for (auto i : flushCheck) {                 //FlushCheck free'd appropriately
            i = nullptr;
        }
        flushCheck.clear();
        for (auto i : flushCards) {                 //FlushCards free'd appropriately
            for (auto k : i) {
                k = nullptr;
            }
            i.clear();
        }
        flushCards.clear();
        for (auto i : straightCards) {              //StraightCards free'd appropriately
            for (auto k : i) {
                k = nullptr;
            }
            i.clear();
        }
    //std::cout << "\n\nTest 38\n\n";
    }

//******
    void Hand::CPUDiscard(Deck& dInput, std::vector<int>& selections) {               //NEED TO CHANGE THIS FUNCTIONS LOGIC TO ALLOW FOR PLAYER STATS TO COME INTO PLAY!!!!!!!
        std::vector<int> cardNums;
        //std::cout << "\n\nselections = " << selections.size() << "\n\n";
        for (int iter = 0; iter < selections.size(); iter++) {          //MIGHT NOT BE NECESSARY!!
          //  std::cout << "\n\nIter = " << iter << "\n\n";               //!!!!!!!!!!!!!!
            if (cardNums.size() > 0) {                                  //!!!!!!!!!!!!!!
                /*for (auto i : cardNums) {                               //!!!!!!!!!!!!!!
                     for (auto &k : selections) {
                        std::cout << "\n\nPrev k = " << k << "\n\n";
                        if (k > i) {
                            k--;
                            std::cout << "\n\nPost k = " << k << "\n\n";
                        }
                    }
                }
                */

                selections.at(iter) -= iter;
            }
           // std::cout << selections.at(iter);
            if (selections.at(iter) < vCards.size()) {
                dInput.ToDiscard(vCards.at(selections.at(iter)));
                vCards.erase(vCards.begin() + (selections.at(iter)));
                cardNums.push_back(selections.at(iter));
            } else {
                std::cout << "\n\nError - selection is " << selections.at(iter) << " whereas hand size is " << vCards.size() << "\n\n";
            }
        }

        DrawCard(selections.size(), dInput);
        SortHand();
    }
//******
    void Hand::ShowScore(int iOutput, double iTotal) const {
        switch (iOutput) {
            case 100 : std::cout << "\nOne pair!\n"; break;
            case 200 : std::cout << "\nTwo pair!\n"; break;
            case 300 : std::cout << "\nThree of a kind!\n"; break;
            case 400 : std::cout << "\nStraight!\n"; break;
            case 500 : std::cout << "\nFlush!\n"; break;
            case 600 : std::cout << "\nFull House!!\n"; break;
            case 800 : std::cout << "\nFour of a Kind!!\n"; break;
            case 900 : {
                if (iTotal == 9999999999.0)
                    std::cout << "\nHoly moly... ROYAL FLUSH!!!!!\n";
                else
                    std::cout << "\nStraight Flush!!!\n";
                break;
            }
            default : std::cout << "\nNo hand.\n";
        }
    }


//******
    Hand::~Hand() {

    }
