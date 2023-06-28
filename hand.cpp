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
        std::cout << "\n";
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
    void Hand::PrintSelection(std::vector<Card> selection) const {                                  //Print's the player's a selection of cards.
        std::cout << "\n";
        for (auto& iter : selection) {
            std::cout << " ,,,,,,, ";
        }
        std::cout << "\n";


        for (auto& iter : selection) {
            std::cout << " |" << iter.GetSuitSym() << "  " << iter.GetNumStr() << "| ";
        }
        std::cout << "\n";

        for (auto& iter : selection) {
            std::cout << " |     | ";
        }
        std::cout << "\n";

        for (auto& iter : selection) {
            std::cout << " |" << iter.GetSuitStr() << "| ";
        }
        std::cout << "\n";

        for (auto& iter : selection) {
            std::cout << " |     | ";
        }
        std::cout << "\n";

        for (auto& iter : selection) {
            std::cout << " |" << iter.GetNumStr() << "  " << iter.GetSuitSym() << "| ";
        }
        std::cout << "\n";

         for (auto& iter : selection) {
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

        int discardCount = 0;                                               //Variable stores the amount of cards the player will discard
        int discardChoice = 0;                                              //The actual card they will discard on this pass of the discard iteration series
        bool hasAce = false;                                                //Checks if the player has an ace - important for determining if the player can discard 4 cards
        std::vector<Card> tempVect;                                         //Vector that holds all aces the player has - used for allowing the player to select which ace to drop
                                                                            //...when discarding 4 and holding more than 1 ace
        Card* tempCard = nullptr;                                           //Pointer that points to individual cards and holds their location

        for (auto i : vCards) {                                             //Parses the hand - if an ace is discovered in any location, the hasAce bool is turned on
            if (i.GetNum() == ACE) {
                hasAce = true;
            }
        }

        if (hasAce) {                                                       //If the player has an ace, their ace is pushed onto the tempVect vector
            for (auto i : vCards) {                                         //*********THIS SEEMS PRETTY REDUNDANT**********
                if (i.GetNum() == ACE) {                                    //...Can this just be implemented in the above for loop??
                    tempVect.push_back(i);
                }
            }
        }

        while (discardCount < 1 || discardCount > 5) {                                      //Uses discardCount starting at 0 to begin loop - checks for proper input for card discard count
            std::cout << "How many cards would you like to discard?\n\n";
            std::cin >> discardCount;
            if (discardCount == 0 && std::cin) {                                                //If they discard 0, return to the calling function with no further action
                return;
            } else if (discardCount == 4) {                                                     //If they discard 4, checks if they have an ace.  If not, discardCount is set to 0, as they cannot discard 4
                if (!hasAce) {
                    discardCount = 0;
                    std::cout << "\nCannot discard 4 - no aces\n";
                }
            } else if (discardCount > 4 || discardCount < 1 || !std::cin) {                     //If they discard less than 0 or greater than 4, OR input an invalid character, buffer is cleared and count set to 0
                discardCount = 0;                                                                   //They are primed to try again.

                std::cout << "\nInvalid entry - enter a number between 1 and 3, or up to 4 if you have an ace\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }

        if (hasAce && discardCount == 4) {                                                  //If they are dropping all but their ace, the player can choose which ace to keep
            int keepChoice = 0;
            if (tempVect.size() > 1) {
                PrintAces();                                                                    //Prints all aces
                while (keepChoice < 1 || keepChoice > tempVect.size()) {                        //Player chooses between 1 and the number of aces total
                    std::cout << "\nChoose which ace keep\n\n";
                    std::cin >> keepChoice;
                    if (!std::cin || keepChoice < 1 || keepChoice > tempVect.size()) {          //if the player makes an invalid input, they are prompted to try again.
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cout << "\n\nInvalid entry.  Please try again.\n";
                    }
                    tempCard = &(tempVect.at(keepChoice - 1));                                  //The ace they choose is stored at tempCard
                }
            } else {
                tempCard = &(tempVect.at(0));                                               //if they only have one ace, the first card is chosen, as it's the most valuable card
            }                                                                               //...and the most valuable cards always come first when sorted

        }

        if (discardCount == 4) {                                                            //Parses the entire hand - everything that is NOT the user's selected ace is discarded
            for (int iter = vCards.size(); iter > 0; iter--) {
                if (tempCard->GetNum() != vCards.at(iter - 1).GetNum()) {
                    dInput.ToDiscard(vCards.at(iter - 1));
                    vCards.erase(vCards.begin() + (iter - 1));
                    PrintHand();
                } else if (tempCard->GetSuit() != vCards.at(iter - 1).GetSuit()) {
                    dInput.ToDiscard(vCards.at(iter - 1));
                    vCards.erase(vCards.begin() + (iter - 1));
                    PrintHand();
                }
            }
        } else {                                                                            //If they are not discarding 4 cards, the user can select up to X times, where X is the
            for (int iter = 0; iter < discardCount; iter++) {                               //...number of cards they are choosing to discard, which cards to discard from their hand

                discardChoice = -1;                                                         //Setting discardChoice to -1 "primes" the loop
                bool cancelEarly = false;                                                   //Bool that turns on if they player chooses to stop discarding cards
                int handSize = vCards.size();
                while ((discardChoice < 1 || discardChoice > handSize) && !cancelEarly) {
                    PrintHand();                                                            //Prints the user's hand on each iteration - shrinks for each discarded card
                    std::cout << "\nChoose card #" << iter + 1 << " to discard.\n"
                              << "Enter 0 to stop discarding cards\n\n";
                    std::cin >> discardChoice;
                    if (discardChoice == 0 && std::cin) {                                               //If they choose 0 and not an invalid value, discardCount is set to iter
                        discardCount = iter;                                                            //...and cancelEarly turns on
                        cancelEarly = true;
                    } else if (discardChoice < 1 || discardChoice > handSize || !std::cin) {            //Invalid entry - while loop repeats, buffer cleared
                        discardChoice = -1;
                        std::cout << "\nInvalid entry - enter a number between 1 and " << vCards.size() << "\n";
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                    }
                }
                if (!cancelEarly) {                                         //If the player clears the while loop and isn't canceling early, the particular card selected is discarded
                    dInput.ToDiscard(vCards.at(discardChoice - 1));         //...and the while loop is primed once more
                    vCards.erase(vCards.begin() + (discardChoice - 1));
                    std::cout << "\n\n";
                    discardChoice = -1;
                }
            }
        }
        DrawCard(discardCount, dInput);                 //After all cards selected are discarded, the player draws that many cards from the deck, and their hand is sorted once more
        SortHand();
    }

//******
    void Hand::DiscardHand(Deck& dInput) {                      //This function does the same as above, but discards the player's entire hand automatically
        for (auto i : vCards) {
            dInput.ToDiscard(i);
        }
        for (int iter = vCards.size(); iter > 0; iter--) {
            vCards.erase(vCards.begin() + (iter - 1));
//          vCards.resize(iter - 1);
        }
        vCards.clear();
    }

//******                                                                //***CPU FUNCTION***    -   This function is specifically for the CPU to select the cards it wants to discard

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


        std::vector<std::vector<Card*>> straightCards;
        std::vector<std::vector<Card*>> flushCards;

        for (int iter = 0; iter < vCards.size(); iter++) {
            Card* i = &vCards.at(iter);
            if (i->GetNum() == ACE) {
                hasAce = true;
            }
            if (prevCard == nullptr) {
                prevCard = i;
            }
            else {
                if (i->GetNum() == prevCard->GetNum()) {

                    if (streak) {
                        goodCards.push_back(i);
                    }
                    else {
                        streak = true;
                        goodCards.push_back(prevCard);
                        goodCards.push_back(i);
                    }
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
                }
            }
            prevCard = i;
        }

//******
        if (goodCards.size() == 0) {
            while (straightCheck.size() > 0) {
                std::vector<int> tempNums;
                CardNum tempNum;
                for (int iter = 0; iter < straightCheck.size(); iter++) {
                    if (iter == 0) {
                        tempNum = straightCheck.at(iter)->GetNum();
                        tempNums.push_back(iter);
                    }
                    else {
                        if (straightCheck.at(iter)->GetNum() < tempNum && straightCheck.at(iter)->GetNum() > tempNum - 5) {
                            tempNums.push_back(iter);
                        }
                    }
                }
                std::vector<Card*> tempVect;
                for (auto i : tempNums) {
                    tempVect.push_back(straightCheck.at(i));
                }
                int rangeCount = 0;
                for (auto i : tempNums) {
                    i -= rangeCount;
                    straightCheck.at(i) = nullptr;
                    straightCheck.erase(straightCheck.begin() - i);
                    rangeCount++;
                }
                straightCards.push_back(tempVect);
                tempVect.clear();
            }
            while (flushCheck.size() > 0) {
                std::vector<int> tempNums;
                CardSuit tempSuit;
                for (int iter = 0; iter < flushCheck.size(); iter++) {
                    if (iter == 0) {
                        tempSuit = flushCheck.at(iter)->GetSuit();
                        tempNums.push_back(iter);
                    }
                    else {
                        if (tempSuit == flushCheck.at(iter)->GetSuit()) {
                            tempNums.push_back(iter);
                        }
                    }
                }
                std::vector<Card*> tempVect;
                for (auto i : tempNums) {
                    tempVect.push_back(flushCheck.at(i));
                }
                int rangeCheck = 0;
                for (auto i : tempNums) {
                    i -= rangeCheck;
                    flushCheck.at(i) = nullptr;
                    flushCheck.erase(flushCheck.begin() + i);
                    rangeCheck++;
                }
                flushCards.push_back(tempVect);
                for (auto i : tempVect) {
                    i = nullptr;
                }
                tempVect.clear();                                                   //Tempvect free'd appropriately
            }
            int flushNum = 0;
            int straightNum = 0;
            for (auto i : flushCards) {
                if (i.size() > flushNum) {
                    flushNum = i.size();
                }
            }

            for (auto i : straightCards) {
                if (i.size() > straightNum) {
                    straightNum = i.size();
                }
            }

            int biggestNum = 0;
            int biggestVect = 0;
            badCards.clear();
            if (flushNum >= straightNum) {
                for (int iter = 0; iter < flushCards.size(); iter++) {
                    if (flushCards.at(iter).size() > biggestNum) {
                        biggestNum = flushCards.at(iter).size();
                        biggestVect = iter;
                    }
                }

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
            }
            else {
                for (int iter = 0; iter < straightCards.size(); iter++) {
                    if (straightCards.at(iter).size() > biggestNum) {
                        biggestNum = straightCards.at(iter).size();
                        biggestVect = iter;
                    }
                }

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
            }
        }

        //**
        if (badCards.size() > 3) {
            if (hasAce) {
                discardCount = 4;
                std::cout << "The player is discarding everything but their ace.\n";
                PrintCard(vCards.at(0));
            } else {
                discardCount = 3;
            }
        } else {
            discardCount = badCards.size();

        }

        for (int iter = 0; iter < vCards.size(); iter++) {
            for (auto k : badCards) {
                if ((k->GetNum() == vCards.at(iter).GetNum()) && (k->GetSuit() == vCards.at(iter).GetSuit())) {
                    selections.push_back(iter);
                }
            }
        }

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
    }

//******
    void Hand::CPUDiscard(Deck& dInput, std::vector<int>& selections) {               //NEED TO CHANGE THIS FUNCTIONS LOGIC TO ALLOW FOR PLAYER STATS TO COME INTO PLAY!!!!!!!
        std::vector<int> cardNums;
        std::vector<Card> cardVect;
        for (int iter = 0; iter < selections.size(); iter++) {
            if (cardNums.size() > 0) {
                selections.at(iter) -= iter;
            }
            cardVect.push_back(vCards.at(selections.at(iter)));
            dInput.ToDiscard(vCards.at(selections.at(iter)));
            vCards.erase(vCards.begin() + (selections.at(iter)));
            cardNums.push_back(selections.at(iter));

        }
        if (cardVect.size() > 0) {
            std::cout << "The player discards the following cards:\n";
            PrintSelection(cardVect);
            DrawCard(selections.size(), dInput);
            SortHand();
        } else {
            std::cout << "The player keeps all cards in their hand.\n\n";
        }
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
