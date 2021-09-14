//
// Created by thadd on 6/23/2021.
//

#include "opponentBoard.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//generic constructor for the class
opponentBoard::opponentBoard() {
    cout << "Computer's Battleship Board" << endl;
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    setUpBoard();
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
}

//setUp the initial battleship board with hidden positions
void opponentBoard::setUpBoard() {
    int rows = 11;
    int cols = 11;
    char alpha = 'A';
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if( i == 0 && j != 0){ //print header row
                _board[i][j] = to_string(j);
            }
            else if(j == 0 && i == 0){ //first slot is a space
                    _board[i][j] = " ";
            }
            else if(j == 0 && i > 0) {
                _board[i][j] = alpha; //first column letters
                alpha++;
            }
            else{
                _board[i][j] = '*'; //filler for the rest of the board
            }
        }
    }
    printBoard();
}

//initialize the 5 battle ship locations on the board
void opponentBoard::shipLocations(){
    strikeLocation info;

    //carrier Ship placed at A10-E10
    _carrierShip.name = "Carrier";
    _carrierShip.shipSize = 5;
    for(int i = 0; i < _carrierShip.shipSize; i++) {
        info.letterRow= i+1;
        info.numberCol = 10;
        _carrierShip.coordinates.push_back(info);
    }
    //battleship Ship placed at H2-H5
    _battleShip.name = "Battleship";
    _battleShip.shipSize = 4;
    for(int i = 0; i < _battleShip.shipSize; i++) {
        info.letterRow= 8;
        info.numberCol = i+2;
        _battleShip.coordinates.push_back(info);
    }

    //cruiser Ship placed at C6-E6
    _cruiser.name = "Cruiser";
    _cruiser.shipSize = 3;
    for(int i = 0; i < _cruiser.shipSize; i++) {
        info.letterRow= i+3;
        info.numberCol = 6;
        _cruiser.coordinates.push_back(info);
    }

    //submarine Ship placed at H8-J8
    _submarine.name = "Submarine";
    _submarine.shipSize = 3;
    for(int i = 0; i < _submarine.shipSize; i++) {
        info.letterRow= i+8;
        info.numberCol = 8;
        _submarine.coordinates.push_back(info);
    }

    //destroyer Ship placed at B3-C3
    _destroyer.name = "Destroyer";
    _destroyer.shipSize = 2;
    for(int i = 0; i < _destroyer.shipSize; i++) {
        info.letterRow= i+2;
        info.numberCol = 3;
        _destroyer.coordinates.push_back(info);
    }


}

//translate the user guess such as "A1" into a readable matrix value like "1,1" in this case
string opponentBoard::translateGuess(string &guess) {
    struct header { //header of the board
        char letter;
        int number;
    };
    //build a vector to compare the guess Letter to and then translate it to a number
    vector<header> translate;
    header info;
    char alpha = 'A';
    char firstLetter = toupper(guess[0]); //get the letter of the guess, guards against lower case inputs
    for(int i = 0; i < 10; i++){
        info.letter = alpha;
        info.number = i + 1;
        translate.push_back(info);
        alpha++;
    }
    //check to see if the user guess letter is a valid input and if so return the corresponding matrix value
    string numTrans;
    bool count = false;
    for(int i = 0; i < translate.size(); i++ ){
        if(translate.at(i).letter == firstLetter) {
            guess.erase(guess.begin()); //erase the letter so the replacement of the number can happen
            numTrans = to_string(translate.at(i).number); //number to replace the guess location letter
            numTrans += "," + guess; //add to temp string
            guess = numTrans; //update guess
            count = true; //count for a correct letter entry
        }
    }
    if (!count){ //if the user letter was not a valid input then change the guess to not valid
        guess = "Not a Valid Guess";
    }
    return guess;
}

//convert guess from "1,10" and return in a location struct
strikeLocation opponentBoard::guessInfo(string &guess) {
    strikeLocation info;
    string row;
    string column;
    int rowNum;
    int colNum;
    int commaIndex = guess.find(','); //row and column is separated by a comma
    //get row number
    for(int i = 0; i < commaIndex; i++){
        row += guess[i];
    }
    //get column number
    for(int i = commaIndex + 1; i < guess.size(); i++){
        column += guess[i];
    }
    //convert string to an integer to help update the made guesses vector
    rowNum = stoi(row);
    colNum = stoi(column);
    info.letterRow = rowNum;
    info.numberCol = colNum;
    return info;
}

//check if the user guess has been made or not, input type is in the form of the info struct
//false if the guess has not been made, true if it has
bool opponentBoard::madeUserAttacks(string &guess, vector<strikeLocation> &userAttacks) {
    bool temp = false; //false if the guess has not been made, true if it has
    strikeLocation info = guessInfo(guess);
    for(int i = 0; i < userAttacks.size(); i++){
        if(userAttacks.at(i).letterRow == info.letterRow && userAttacks.at(i).numberCol == info.numberCol){
            temp = true; //guess has been made
            break; //break, no longer need to compare if a match has been found
            }
        else{
            temp = false; //guess has not been made
        }
    }
    return temp;
}

//check if the user guess is valid or not, return true if so and false if not
bool opponentBoard::checkAttack(string &guess) {
    translateGuess(guess); //translate the guess into a readable row and column string
    int commaIndex;
    int digitCount = 0; //count the number of digits present in the column part of the guess
    bool temp = false; //storage for if the attack is valid
    if(guess == "Not a Valid Guess"){ //a false case from the translate function
        temp = false; //not valid;
    }
    else{
        commaIndex = guess.find(',');
        for(int i = commaIndex; i < guess.size(); i++) {
            if (isdigit(guess[i])) {
                digitCount += 1; //count the number of digits in the column portion of the guess
            }
            if (digitCount <= 2) {
                //check for extra characters in user input
                if (i != commaIndex && (ispunct(guess[i]) || isalpha(guess[i]))) {
                    temp = false; //not valid
                    break; //break because user input is for sure incorrect
                }
                if (commaIndex == guess.size() - 2) {//means column entry is single digit
                    if (i == commaIndex + 1 && guess[i] != '0') {
                        temp = true; //valid
                    }
                } else if (i == guess.size() - 1) {
                    if (guess[i] == '0' && guess[i - 1] == '1') { //column entry is double digit, 10 is only valid
                        temp = true; //valid
                    }
                }
            }
        }
    }
    return temp;
}
//get user input function, takes in the current guess, main loop count, and storage vector for valid user guesses
string opponentBoard::getUserInput(string &guess, int &count, vector<strikeLocation> &userAttacks) {
    //check that the userGuess is valid
    strikeLocation info;
    bool valid = false;
    bool repeat = true;
    bool broken;
    if (count == 0){ //first user guess
        cout << "Your turn to fire!! Enter your strike coordinates." << endl;
        cout << "Strike coordinates (Ex: A10): ";
        cin >> guess;
        cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
        while (!checkAttack(guess)) { //check if the first input is valid, repeat until valid
            cout << "Invalid Coordinates. Please Enter Valid Coordinates." << endl;
            cout << "Enter your strike coordinates" << endl << "Strike coordinates (Ex: A10): ";
            cin >> guess;
            cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
        }
        //guess is valid, append the first guess to the vector storing valid guesses
        info = guessInfo(guess);
        userAttacks.push_back(info);
    }
    else {
        while (!valid && repeat) { //while the user input is not valid and is a repeat
            if(broken) { //if broken is true
               cout << "Enter your strike coordinates" << endl << "Strike coordinates (Ex: A10): ";
            }
            else{
                cout << "Your turn to fire!!" << endl << "Enter your strike coordinates" << endl;
                cout << "Strike coordinates (Ex: A10): ";
            }
            cin >> guess;
            cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
            broken = false; //reset broken status
            while (!checkAttack(guess)) { //guess is invalid, repeat til invalid
                cout << "Invalid Coordinates. Please Enter Valid Coordinates." << endl;
                cout << "Enter your strike coordinates." << endl << "Strike coordinates (Ex: A10): ";
                cin >> guess;
                cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
            }
            valid = true; //guess is valid
            while(madeUserAttacks(guess,userAttacks)){ //guess has been made, repeat until new guess
                cout << "You have entered those coordinates before. Please enter new coordinates." << endl;
                cout << "Strike coordinates (Ex: A10): ";
                cin >> guess;
                cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
                valid = checkAttack(guess); //check if the guess is valid
                if(!valid){ //not valid
                    cout <<"Invalid Coordinates. Please Enter Valid Coordinates." << endl;
                    broken = true; //broken status due to invalid input
                    break;
                }
            }
            if(broken){ //if broken is true
                repeat = true; //still haven't found a non repeating guess, guess was invalid
            }
            else {
                repeat = false; //guess is non repeating
            }
            if (valid && !repeat) { //if guess is valid and new, add to the vector of previous made valid guesses
                info = guessInfo(guess);
                userAttacks.push_back(info);
            }
        }
    }
    return guess;
}

//update the board with the user guess, "X" if hit "O" if miss
//counts the number of hits and returns the value
int opponentBoard::updateBoard(string &guess, int &userHitCounter) {
    shipLocations(); //bring in the ship locations
    strikeLocation info = guessInfo(guess);
    int strikeRow = info.letterRow;
    int strikeCol = info.numberCol;
    bool tempHit = false;

    cout << "Computer's Battleship Board" << endl;
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    //check every ship location to see if the guessed location is a hit
    for(int i = 0; i < _carrierShip.shipSize; i++) {
        if ( i < 2){ //check destroyer location
            if(_destroyer.coordinates.at(i).letterRow == strikeRow
                && _destroyer.coordinates.at(i).numberCol == strikeCol){
                tempHit = true;
                _destroyer.hits++; //add a hit to the destroyer
                userHitCounter += 1; //add a hit to the hit counter
                _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
                break; //break for loop because there can only be one hit
            }
        }
        if (i < 3){ //check cruiser and submarine location
            if(_cruiser.coordinates.at(i).letterRow == strikeRow
               && _cruiser.coordinates.at(i).numberCol == strikeCol){
                tempHit = true;
                _cruiser.hits++; //add a hit to the cruiser
                userHitCounter += 1; //add a hit to the hit counter
                _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
                break;
            }
            if(_submarine.coordinates.at(i).letterRow == strikeRow
               && _submarine.coordinates.at(i).numberCol == strikeCol){
                tempHit = true;
                _submarine.hits++; //add a hit to the submarine
                userHitCounter += 1; //add a hit to the hit counter
                _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
                break;
            }
        }
        if (i < 4){ //check battleship location
            if(_battleShip.coordinates.at(i).letterRow == strikeRow
               && _battleShip.coordinates.at(i).numberCol == strikeCol){
                tempHit = true;
                _battleShip.hits++; //add a hit to the battleship
                userHitCounter += 1; //add a hit to the hit counter
                _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
                break;
            }
        }
        //check carrierShip location
        if(_carrierShip.coordinates.at(i).letterRow == strikeRow
           && _carrierShip.coordinates.at(i).numberCol == strikeCol){
            tempHit = true;
            _carrierShip.hits++; //add a hit to the carrier ship
            userHitCounter += 1; //add a hit to the hit counter
            _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
            break;
        }
    }
    if(!tempHit){ //if there was no hit found
        _board[strikeRow][strikeCol] = "O"; //replace location with an 'O'
    }
    printBoard(); //update board by printing it
    return userHitCounter; // if there are 17 hits then the user has won
}

void opponentBoard::hitMissSunk(int &userHitMissVariable, int &userHitCounter) {
    if(userHitCounter > userHitMissVariable){
        cout << "Your last coordinates HIT!" << endl;
    }
    else{
        cout << "Your last coordinates MISSED" << endl;
    }
    if(_carrierShip.hits == 5){
        cout<< "You sunk the computer's " << _carrierShip.name << " ship!" << endl;
        _carrierShip.hits++; //update so this statement won't print again
    }
    else if(_battleShip.hits == 4){
        cout<< "You sunk the computer's " << _battleShip.name << "!" << endl;
        _battleShip.hits++; //update so this statement won't print again
    }
    else if(_cruiser.hits == 3){
        cout<< "You sunk the computer's " << _cruiser.name << " ship!" << endl;
        _cruiser.hits++; //update so this statement won't print again
    }
    else if(_submarine.hits == 3){
        cout<< "You sunk the computer's " << _submarine.name << "!" << endl;
        _submarine.hits++; //update so this statement won't print again
    }
    else if(_destroyer.hits == 2){
        cout<< "You sunk the computer's " << _destroyer.name << "!" << endl;
        _destroyer.hits++; //update so this statement won't print again
    }
}

//function for printing the computer's board
void opponentBoard::printBoard() {
    int rows = 11;
    int cols = 11;
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << _board[i][j];
            if (j == cols - 1){
                cout << endl;
            }
        }
    }
}