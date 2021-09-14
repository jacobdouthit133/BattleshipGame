/* CSCI 261: Final Project: BattleShip Game
*
        * Author: Thaddious Douthit
*
* A user interactive battleship game
*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include "opponentBoard.h"
#include "userBoard.h"
#include "strikeLocation.h"

using namespace std;

int main() {
    //there are three random computer guess files, all are unique, contain all possible locations with no repeats/errors
    // 1) "computer_gameV1.txt"
    // 2) "computer_gameV2.txt"
    // 3) "computer_gameV3.txt"
    //the game is going to randomly pick one
    //create a struct vector to compare and store answers
    vector<strikeLocation> userAttacks;
    string userAttackCoordinates; //user coordinate guess

    //create a struct vector to store computer strike locations in
    vector<strikeLocation> computerAttackLocations;
    //computer strike location temporary variable
    strikeLocation computerCoordinates;
    //hit counters and number of attacks counter
    int userHitCounter = 0;
    int opponentHitCounter = 0;
    int count = 0; //count the number of user attacks made
    int opponentHitMissVariable;
    int userHitMissVariable;
    //set up the game
    userBoard uBoard; //initialize user board
    string fileName = uBoard.getFileName();
    uBoard.getComputerAttacks(fileName, computerAttackLocations); //get and store the input attacks
    opponentBoard compBoard; //initialize computer board
    while(userHitCounter < 17 && opponentHitCounter < 17) {
        //capture the current hit counters to determine if a hit occurred later on
        opponentHitMissVariable = opponentHitCounter;
        userHitMissVariable = userHitCounter;
        //get user coordinates input guess
       compBoard.getUserInput(userAttackCoordinates, count, userAttacks);

       //update opponent board
       compBoard.updateBoard(userAttackCoordinates, userHitCounter);
       cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;

       // print if it was a hit or miss or sunk ship
       compBoard.hitMissSunk(userHitMissVariable,userHitCounter);
       cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;

       //get computer attack coordinates
       computerCoordinates = uBoard.computerTarget(count,computerAttackLocations);

       //update the user board
       uBoard.updateUserBoard(computerCoordinates,opponentHitCounter);
       cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;

       //print if it was a hit or miss or sunk ship
       uBoard.hitMissSunk(opponentHitMissVariable,opponentHitCounter);
       cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
       count++; //update number of attacks from each side
    }
    cout << "End of Game" << endl;
    if(userHitCounter == 17 && opponentHitCounter < 17){
        cout << "You won!!" << endl;
    }
    else if(opponentHitCounter == 17 && userHitCounter < 17){
        cout << "The computer won... you lost :(" << endl;
    }
    else{
        cout << "It's a tie!?!" << endl;
    }
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    return 0;
}
