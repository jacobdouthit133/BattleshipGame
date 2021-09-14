//
// Created by thadd on 6/23/2021.
//

#ifndef FINAL_PROJECT_OPPONENTBOARD_H
#define FINAL_PROJECT_OPPONENTBOARD_H

#include <string>
#include <vector>
#include "strikeLocation.h"
#include "shipLocation.h"

using namespace std;

class opponentBoard {
public:
    opponentBoard();
    void setUpBoard();
    string getUserInput(string &guess, int &count, vector<strikeLocation>& userAttacks);
    int updateBoard(string &guess, int &userHitCounter);
    void hitMissSunk(int &userhitMissVariable, int &userHitCounter);
private:
    string _board[11][11];
    shipLocation _carrierShip;
    shipLocation _battleShip;
    shipLocation _cruiser;
    shipLocation _submarine;
    shipLocation _destroyer;
    void shipLocations();
    string translateGuess(string &guess);
    strikeLocation guessInfo(string &guess);
    bool madeUserAttacks(string &guess, vector<strikeLocation> &userAttacks);
    bool checkAttack(string &guess);
    void printBoard();
};


#endif //FINAL_PROJECT_OPPONENTBOARD_H
