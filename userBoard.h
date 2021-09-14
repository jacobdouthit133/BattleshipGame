//
// Created by thadd on 6/23/2021.
//

#ifndef FINAL_PROJECT_USERBOARD_H
#define FINAL_PROJECT_USERBOARD_H

#include <string>
#include <vector>
#include "strikeLocation.h"
#include "shipLocation.h"

using namespace std;

class userBoard {
public:
    userBoard();
    void setUpBoard();
    void getShipLocations();
    string getFileName();
    void getComputerAttacks(const string &inputFileName, vector<strikeLocation>& computerAttackLocations);
    strikeLocation computerTarget(int &count, vector<strikeLocation>& computerAttackLocations);
    int updateUserBoard(strikeLocation &strikeInfo, int &opponentHitCounter);
    void hitMissSunk(int &opponentHitMissVariable, int &opponentHitCounter);
private:
    string _board[11][11];
    shipLocation _carrierShip;
    shipLocation _battleShip;
    shipLocation _cruiser;
    shipLocation _submarine;
    shipLocation _destroyer;
    bool checkPlacement(struct shipLocation &ship);
    void shipPlacer(struct shipLocation &ship, string &orientation , string &startCoordinates);
    bool checkShipLocation(int shipSize, string &direction , string &startCoordinates);
    bool checkDirection(string &direction);
    bool checkCoordinates(string &startCoordinates);
    string translateDirection(string &direction);
    string translateCoordinates(string &startCoordinates);
    strikeLocation coordinateInfo(string &startCoordinates);
    string rowNumConvert(int rowNumber);
    void printPlacementStatements(struct shipLocation &ship, string &orientation, string &startCoordinates);
    void displayUpdatedBoard();
    void printBoard();
};


#endif //FINAL_PROJECT_USERBOARD_H
