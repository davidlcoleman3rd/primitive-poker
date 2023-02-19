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

    Hand::Hand(Deck& dInput) {
        GetHand(dInput);
    }

//******
    void Hand::GetHand(Deck& dInput) {
        DrawCard(5, dInput);
    }

//******
    void Hand::SortHand() {
        std::vector<Card> vTempSort;                                //
        int iSize = vCards.size();
        Card* tempCard = nullptr;
        for (int iCount = 0; iCount < iSize; iCount++) {
            int vCardSize = vCards.size();
            for (int iter = 0; iter < vCardSize; iter++) {
                CardNum cnFinal;
                CardNum cnTemp;
                cnTemp = vCards.at(iter).GetNum();
                Card cardTemp(vCards.at(iter));
                if (cnTemp > cnFinal || iter == 0) {
                    if (tempCard != nullptr) {
                        delete tempCard;
                        tempCard = nullptr;
                    }
                    cnFinal = cnTemp;
                    tempCard =  new Card(cardTemp);
                }
            }
            vTempSort.push_back(*(tempCard));
            for (int iter = 0; iter < int(vCards.size()); iter++) {
                if (vCards.at(iter) == *(tempCard)) {
                    vCards.erase(vCards.begin() + iter);
                }
            }
            delete tempCard;
            tempCard = nullptr;
        }
        vCards = vTempSort;
    }

//******
    void Hand::DrawCard(int iCount, Deck& dInput) {
        for (int iter = 0; iter < iCount; iter++) {
            vCards.push_back(dInput.DealCard(HAND_STATE));
        }
    }

//******
    void Hand::Discard(std::vector<int> vDiscard, Deck& dInput) {
        int iSize = 0;
        std::vector<int>::iterator iter;
        for (iter = vDiscard.begin(); iter < vDiscard.end(); iter++) {
            vCards.erase(vCards.begin() + *iter);
            iSize++;
        }
        DrawCard(iSize, dInput);                        //Draws cards for the user
    }

//******
    void Hand::PrintHand() const {
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
    double Hand::CountPoints() {
        SortHand();
        double totalScore = 0;
        int outputScore = 0;
        int iteration = 0;
        CardSuit csTemp;
        CardNum cnTemp;


        for (auto& iter : vCards) {
            //            13 ^ -x, where x is 13 - the value of the card + 1; This means ACE will return 1.0, whereas 2 will return 4E-14, etc
            //              MAKE A TABLE FOR THIS
            totalScore += double(1 / std::pow(13,(13 - (int(iter.GetNum()) + 1))));
        }

        int streak = 0;
        bool hasPair = false;
        bool hasTrips = false;
        bool hasQuads = false;
        bool twoPair = false;
        bool fullHouse = false;
        bool tripsFirst = false;
        std::vector<int> StreakedCards;
        for (auto& iter : vCards) {
            if (iteration > 0) {
                if (cnTemp == iter.GetNum()) {
                    if (hasPair && streak == 1) {
                        hasTrips = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else if (hasTrips && streak == 2) {
                        hasQuads = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else if (hasTrips && streak == 0) {
                        fullHouse = true;
                        tripsFirst = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        hasPair = true;
                        streak++;
                    }
                    else if (hasPair && streak == 0) {
                        twoPair = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else if (twoPair) {
                        hasTrips = true;
                        hasPair = true;
                        fullHouse = true;
                        twoPair = false;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else {
                        hasPair = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                }
                else {
                    streak = 0;
                }
            }
            cnTemp = iter.GetNum();
            iteration++;
        }
        int temp = 0;
        if (hasPair) {
            if (hasTrips) {
                if (hasQuads) {
                    for (auto iter : StreakedCards) {
                        int holdCard = iter;
                        temp += (holdCard * 4000000);
                    }
                    outputScore = 800;
                }
                else if (fullHouse) {
                    if (tripsFirst) {
                        for (int iter = 0; iter < 3; iter++) {
                            int holdCard = iter;
                            temp += (holdCard * 300000);
                        }
                        for (int iter = 3; iter < 5; iter++) {
                            int holdCard = iter;
                            temp += (holdCard * 1000);
                        }
                    }
                    else {
                        for (int iter = 0; iter < 2; iter++) {
                            int holdCard = iter;
                            temp += (holdCard * 1000);
                        }
                        for (int iter = 2; iter < 5; iter++) {
                            int holdCard = iter;
                            temp += (holdCard * 300000);
                        }
                    }
                    outputScore += 600;
                }
                else {
                    for (auto iter : StreakedCards) {
                        int holdCard = iter;
                        temp += (holdCard * 720);
                    }
                    outputScore += 300;
                }
            }
            else if (twoPair) {
                for (auto iter : StreakedCards) {
                    int holdCard = iter;
                    temp += (holdCard * 40);
                }
                outputScore += 200;
            }
            else {
                for (auto iter : StreakedCards) {
                    int holdCard = iter;
                    temp += (holdCard * 10);
                }
                outputScore += 100;
            }
            totalScore += double(temp);
            ShowScore(outputScore, totalScore);
            return totalScore;
        }

        bool isStraight = true;
        bool isFlush = true;
        iteration = 0;
        for (auto& iter : vCards) {
            if (iteration > 0) {
                if (iter.GetSuit() != csTemp) {
                    isFlush = false;
                }
                if (iter.GetNum() != (cnTemp - 1)) {
                    isStraight = false;
                }
                StreakedCards.push_back(int(iter.GetNum()) + 1);
            }
            csTemp = iter.GetSuit();
            cnTemp = iter.GetNum();
            iteration++;
        }

        if (isStraight) {
            if (isFlush) {
                for (auto iter : StreakedCards) {
                    int holdCards = iter;
                    temp += (holdCards * 53000000);
                }
                if (temp == 2760000000.0) {
                    totalScore = 9999999999.0;
                    outputScore = 900;
                    ShowScore(outputScore, totalScore);
                    return totalScore;
                }
                outputScore += 500;

            }
            else {
                for (auto iter : StreakedCards) {
                    int holdCards = iter;
                    temp += (holdCards * 2400);
                }
                outputScore += 400;
            }
            totalScore += double(temp);
        }
        else if (isFlush) {
            for (auto iter : StreakedCards) {
                int holdCards = iter;
                temp += (holdCards * 7200);
                totalScore += double(temp);
            }
        }
        ShowScore(outputScore, totalScore);
        return totalScore;
    }

//******
    double Hand::CountPoints(bool noPrint) {
        SortHand();
        double totalScore = 0;
        int outputScore = 0;
        int iteration = 0;
        CardSuit csTemp;
        CardNum cnTemp;


        for (auto& iter : vCards) {
            //            13 ^ -x, where x is 13 - the value of the card + 1; This means ACE will return 1.0, whereas 2 will return 4E-14, etc
            //              MAKE A TABLE FOR THIS
            totalScore += double(1 / std::pow(13,(13 - (int(iter.GetNum()) + 1))));
        }

        int streak = 0;
        bool hasPair = false;
        bool hasTrips = false;
        bool hasQuads = false;
        bool twoPair = false;
        bool fullHouse = false;
        bool tripsFirst = false;
        std::vector<int> StreakedCards;
        for (auto& iter : vCards) {
            if (iteration > 0) {
                if (cnTemp == iter.GetNum()) {
                    if (hasPair && streak == 1) {
                        hasTrips = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else if (hasTrips && streak == 2) {
                        hasQuads = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else if (hasTrips && streak == 0) {
                        fullHouse = true;
                        tripsFirst = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        hasPair = true;
                        streak++;
                    }
                    else if (hasPair && streak == 0) {
                        twoPair = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else if (twoPair) {
                        hasTrips = true;
                        hasPair = true;
                        fullHouse = true;
                        twoPair = false;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                    else {
                        hasPair = true;
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        StreakedCards.push_back(int(iter.GetNum()) + 1);
                        streak++;
                    }
                }
                else {
                    streak = 0;
                }
            }
            cnTemp = iter.GetNum();
            iteration++;
        }
        int temp = 0;
        if (hasPair) {
            if (hasTrips) {
                if (hasQuads) {
                    for (auto iter : StreakedCards) {
                        int holdCard = iter;
                        temp += (holdCard * 4000000);
                    }
                    outputScore = 800;
                }
                else if (fullHouse) {
                    if (tripsFirst) {
                        for (int iter = 0; iter < 3; iter++) {
                            int holdCard = iter;
                            temp += (holdCard * 300000);
                        }
                        for (int iter = 3; iter < 5; iter++) {
                            int holdCard = iter;
                            temp += (holdCard * 1000);
                        }
                    }
                    else {
                        for (int iter = 0; iter < 2; iter++) {
                            int holdCard = iter;
                            temp += (holdCard * 1000);
                        }
                        for (int iter = 2; iter < 5; iter++) {
                            int holdCard = iter;
                            temp += (holdCard * 300000);
                        }
                    }
                    outputScore += 600;
                }
                else {
                    for (auto iter : StreakedCards) {
                        int holdCard = iter;
                        temp += (holdCard * 720);
                    }
                    outputScore += 300;
                }
            }
            else if (twoPair) {
                for (auto iter : StreakedCards) {
                    int holdCard = iter;
                    temp += (holdCard * 40);
                }
                outputScore += 200;
            }
            else {
                for (auto iter : StreakedCards) {
                    int holdCard = iter;
                    temp += (holdCard * 10);
                }
                outputScore += 100;
            }
            totalScore += double(temp);
//          ShowScore(outputScore, totalScore);
            return totalScore;
        }

        bool isStraight = true;
        bool isFlush = true;
        iteration = 0;
        for (auto& iter : vCards) {
            if (iteration > 0) {
                if (iter.GetSuit() != csTemp) {
                    isFlush = false;
                }
                if (iter.GetNum() != (cnTemp - 1)) {
                    isStraight = false;
                }
                StreakedCards.push_back(int(iter.GetNum()) + 1);
            }
            csTemp = iter.GetSuit();
            cnTemp = iter.GetNum();
            iteration++;
        }

        if (isStraight) {
            if (isFlush) {
                for (auto iter : StreakedCards) {
                    int holdCards = iter;
                    temp += (holdCards * 53000000);
                }
                if (temp == 2760000000.0) {
                    totalScore = 9999999999.0;
                    outputScore = 900;
//                  ShowScore(outputScore, totalScore);
                    return totalScore;
                }
                outputScore += 500;

            }
            else {
                for (auto iter : StreakedCards) {
                    int holdCards = iter;
                    temp += (holdCards * 2400);
                }
                outputScore += 400;
            }
            totalScore += double(temp);
        }
        else if (isFlush) {
            for (auto iter : StreakedCards) {
                int holdCards = iter;
                temp += (holdCards * 7200);
                totalScore += double(temp);
            }
        }
//      ShowScore(outputScore, totalScore);
        return totalScore;
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
