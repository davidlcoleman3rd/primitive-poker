#ifndef GAME_H
#define GAME_H

#include <iostream>                 //For output to the terminal - cout, cin, getline(), setw, etc.
#include <limits>                    //For making sure points are allocated correctly - used for int and float lims
#include "card.h"                   //Card class - These objects are the main building block of the entire game set
#include "deck.h"                   //Deck class - The main point in which cards are drawn and distributed to each player
#include "hand.h"                   //Hand class - The main body by which the player stores their cards
#include "player.h"                 //Player class - the class that serves to represent each plyaer in the game; CPU or physical
#include "circularlList.h"          //circular linked list implementation - used to get and maintain the correct turn order for all
                                    //...players in a single game of poker

struct Score {
    int playerNum;
    double points;
};

//**************************************************

const int FIVE_CARD_DRAW_HANDSIZE = 5;
const int SEVEN_CARD_STUD_HANDSIZE = 7;
const int TEXAS_HOLDEM_HANDSIZE = 2;

//**************************************************

class Game {
private:

public:
    void FiveCardDraw();

//******
    void PrintPot(float);

//******
    void AnteUp(CircularList<Player*>&, Deck&, float&, std::vector<std::vector<float>>&);

//******
    void NewPlayers(int, std::vector<Player*>&, Deck&);

//******
    void GameStart(std::vector<Score>&, std::vector<Player*>&, CircularList<Player*>&);

//******
    void GetTells(CircularList<Player*>&, std::vector<PlayerPerception>);

//******
    void PrintUserHand(CircularList<Player*>&);

//******
    void DiscardCards(CircularList<Player*>&, std::vector<Player*>&,
                  std::vector<Score>&, Deck&, std::vector<PlayerPerception>&);

//******
    void EvaluateCards(std::vector<Score>&, std::vector<Player*>&,
                   CircularList<Player*>&, std::vector<PlayerPerception>&);

//******
    void SetBetLead(int currBet, CircularList<Player*>& turnOrder);

//******
    void BettingRound(float&, std::vector<bool>&, int, float&,
                  CircularList<Player*>&, int&, bool&,
                  std::vector<PlayerPerception>, Deck&,
                  std::vector<std::vector<float>>&);

//******
    void PlayerBet();

//******
    void CPUBet();

//******
    void CallingRound(float&, float&, int&, int&, CircularList<Player*>&,
                  std::vector<bool>, std::vector<PlayerPerception>, Deck&,
                  bool&, std::vector<std::vector<float>>&);

//******
    void PlayerCall();

//******
    void CPUCall();

//******
    void IncrementCurrBet(int&, CircularList<Player*>&);

//******
    void PrintAllHands(CircularList<Player*>&, std::vector<Score>&);

//******
    void CheckWinner(CircularList<Player*>&, std::vector<Score>, float&, std::vector<std::vector<float>>&);

//******
    void PrintCash(CircularList<Player*>&);

//******
    void PlayAgain(CircularList<Player*>&, std::vector<Player*>&, Deck&, bool&);

//******
    void DistributePot(std::vector<std::vector<float>>&, CircularList<Player*>&);

};

#endif // GAME_H
