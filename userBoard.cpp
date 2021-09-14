//
// Created by thadd on 6/23/2021.
//

#include "userBoard.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

//generic constructor for the class
userBoard::userBoard() {
    setUpBoard(); //setup the initial hidden battleship board
    cout << endl << "Welcome to a game of Battleship!!!!" << endl;
    cout << "-" << setfill('-') << setw(34) << "-" << setfill(' ') << endl;
    cout << "Let's first set up Your BattleShip Board" << endl;
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    cout << "Your Battleship Board" << endl;
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    printBoard();
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    getShipLocations(); //get all ship locations
}

//setup the initial battleship board with blank positions
void userBoard::setUpBoard() {
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
}

void userBoard::getShipLocations() {
    //initialize shipNames and sizes
    _carrierShip.name = "Carrier"; _carrierShip.shipSize = 5; _carrierShip.identifier = "C";
    _battleShip.name = "Battleship"; _battleShip.shipSize = 4; _battleShip.identifier = "B";
    _submarine.name = "Submarine"; _submarine.shipSize = 3; _submarine.identifier = "S";
    _cruiser.name = "Cruiser"; _cruiser.shipSize = 3; _cruiser.identifier = "R";
    _destroyer.name = "Destroyer"; _destroyer.shipSize = 2; _destroyer.identifier = "D";

    //place the user carrier on the board
    string carrierOrientation;
    string carrierCoordinates;
    printPlacementStatements(_carrierShip,carrierOrientation,carrierCoordinates);
    //ensure that the carrier inputs are valid and if so update the user board with the carrier ship placement
    shipPlacer(_carrierShip,carrierOrientation,carrierCoordinates);

    //place the user battleship on the board
    string battleshipOrientation;
    string battleshipCoordinates;
    printPlacementStatements(_battleShip,battleshipOrientation,battleshipCoordinates);
    //ensure that the battleship inputs are valid and if so update the user board with the carrier ship placement
    shipPlacer(_battleShip,battleshipOrientation, battleshipCoordinates);

    //place the user submarine on the board
    string submarineOrientation;
    string submarineCoordinates;
    printPlacementStatements(_submarine,submarineOrientation,submarineCoordinates);
    //ensure that the submarine inputs are valid and if so update the user board with the carrier ship placement
    shipPlacer(_submarine,submarineOrientation, submarineCoordinates);

    //place the user cruiser on the board
    string cruiserOrientation;
    string cruiserCoordinates;
    printPlacementStatements(_cruiser,cruiserOrientation,cruiserCoordinates);
    //ensure that the cruiser inputs are valid and if so update the user board with the carrier ship placement
    shipPlacer(_cruiser,cruiserOrientation, cruiserCoordinates);

    //place the user destroyer on the board
    string destroyerOrientation;
    string destroyerCoordinates;
    printPlacementStatements(_destroyer,destroyerOrientation,destroyerCoordinates);
    //ensure that the cruiser inputs are valid and if so update the user board with the carrier ship placement
    shipPlacer(_destroyer,destroyerOrientation,destroyerCoordinates);

    cout << "All ships have been properly placed!!!" << endl;
    cout << "Let the battle commence! Best of Luck!!" << endl;
    cout << "-" << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
}

//get computer attack locations from the input file and store all of them in a vector
void userBoard::getComputerAttacks(const string &inputFileName, vector<strikeLocation> &computerAttackLocations) {
    ifstream inputFile(inputFileName);
    if (inputFile.fail()) {
        cerr << "Error trying to find input file";
        exit(1);
    }
    string attackCoordinates;
    strikeLocation info;
    while(!inputFile.eof()){
        inputFile >> attackCoordinates;
        if(!inputFile.fail()) { //guards against a new line at the end
            translateCoordinates(attackCoordinates);
            info = coordinateInfo(attackCoordinates); //get the row and column from the input
            computerAttackLocations.push_back(info);
        }
    }
}

//take in the vector of all the computer attacks, use the main count to iterate and select the next strike location
strikeLocation userBoard::computerTarget(int &count, vector<strikeLocation> &computerAttackLocations) {
    strikeLocation targetInfo;
    targetInfo.letterRow = computerAttackLocations.at(count).letterRow;
    targetInfo.numberCol = computerAttackLocations.at(count).numberCol;
    string letter = rowNumConvert(targetInfo.letterRow);
    cout << "Computer strikes. Coordinates: " << letter << targetInfo.numberCol << endl;
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    return targetInfo;
}

//place a valid ship on the board function
void userBoard::shipPlacer(struct shipLocation &ship, string &orientation, string &startCoordinates) {
    while (!checkDirection(orientation)) {
        cout << "Not a valid orientation input." << endl;
        cout << "Please enter either a V (for down) or > (for across)" << endl;
        cout << "Enter Orientation: ";
        cin >> orientation;
    }
    while (!checkCoordinates(startCoordinates)) {
        cout << "Invalid Coordinates. Please Enter Valid Coordinates." << endl;
        cout << "Enter starting coordinates: ";
        cin >> startCoordinates;
    }
    while(!checkShipLocation(ship.shipSize, orientation, startCoordinates)){
        cout << "-" << setfill('-') << setw(35) << "-" << setfill(' ') << endl;
        cout << "The " << ship.name << " ship will not fit on the board." << endl;
        cout << "Please enter a valid orientation and starting coordinates." << endl;
        cout << "Enter valid orientation: ";
        cin >> orientation;
        while (!checkDirection(orientation)) {
            cout << "-" << setfill('-') << setw(25) << "-" << setfill(' ') << endl;
            cout << "Not a valid orientation input." << endl;
            cout << "Please enter either a V (for down) or > (for across)" << endl;
            cout << "Enter Orientation: ";
            cin >> orientation;
        }
        cout << "Enter valid starting coordinates (Ex: A10): ";
        cin >> startCoordinates;
        while (!checkCoordinates(startCoordinates)) {
            cout << "Invalid Coordinates. Please Enter Valid Coordinates.";
            cout << "Enter starting coordinates: ";
            cin >> startCoordinates;
        }
    }
    //print the carrier location to the board
    strikeLocation info = coordinateInfo(startCoordinates);
    int row = info.letterRow;
    int column = info.numberCol;
    strikeLocation pushbackInfo;
    if(ship.name == "Carrier") { //first ship to be placed
        if (orientation == "V") { //column is constant
            for (int i = 0; i < ship.shipSize; i++) {
                _board[i + row][column] = ship.identifier; //replace the location with the ship identifier
                pushbackInfo.letterRow = i + row;
                pushbackInfo.numberCol = column;
                ship.coordinates.push_back(pushbackInfo);
            }
        } else { //orientation is > (across), row is constant
            for (int i = 0; i < ship.shipSize; i++) {
                _board[row][i + column] = ship.identifier; //replace the location with the ship identifier
                pushbackInfo.letterRow = row;
                pushbackInfo.numberCol = column + 1;
                ship.coordinates.push_back(pushbackInfo);
            }
        }
        //update board
        displayUpdatedBoard();
    }
    else {
        //going to initialize the position of the ship in order to check for an intersection
        if (orientation == "V") { //column is constant
            for (int i = 0; i < ship.shipSize; i++) {
                pushbackInfo.letterRow = i + row;
                pushbackInfo.numberCol = column;
                ship.coordinates.push_back(pushbackInfo);
            }
        } else { //orientation is > (across), row is constant
            for (int i = 0; i < ship.shipSize; i++) {
                pushbackInfo.letterRow = row;
                pushbackInfo.numberCol = column + i;
                ship.coordinates.push_back(pushbackInfo);
            }
        }
        bool placementStatus = checkPlacement(ship);
        if(placementStatus){ // there is an intersection
            cout << "-" << setfill('-') << setw(54) << "-" << setfill(' ') << endl;
            cout << "The ship coordinates you entered intersected with a previously entered ship" << endl;
            cout << "-" << setfill('-') << setw(54) << "-" << setfill(' ') << endl;
            orientation = ".";
            shipPlacer(ship,orientation,startCoordinates);
        }
        else{
            if (orientation == "V") { //column is constant
                for (int i = 0; i < ship.shipSize; i++) {
                    _board[i + row][column] = ship.identifier;
                }
            } else { //orientation is > (across), row is constant
                for (int i = 0; i < ship.shipSize; i++) {
                    _board[row][column + i] = ship.identifier;
                }
            }
            displayUpdatedBoard();
        }
    }
}

//check to see if the input intersects with any other ship, true if does and false if doesn't
bool userBoard::checkPlacement(struct shipLocation &ship) {
    int row;
    int column;
    bool check = false; //doesn't intersect
    string exceptionLetter;
    //check the ship name and its current letter placement
    //iterate over the ship coordinates
    for (int i = 0; i < ship.shipSize; i++) {
        row = ship.coordinates.at(i).letterRow;
        column = ship.coordinates.at(i).numberCol;
        //check the current letter of the ship coordinates if it something
        // other than its own letter than an intersection has occurred
        if ((_board[row][column] == "C" || _board[row][column] == "B" || _board[row][column] == "S" ||
            _board[row][column] == "R" || _board[row][column] == "D")){
            cout << "-" << setfill('-') << setw(54) << "-" << setfill(' ') << endl;
            cout << "Overlapping Ships Detected!!!" << endl;
            check = true; //intersects
            break; //don't need to check anymore because an intersection has been found
        }
    }
    if(check){ //if an intersection happened clear the contents of the ship coordinates because they are not valid
        ship.coordinates.clear();
    }
    return check;
}

//check the direction input, false if the direction input is not valid, true if it is
bool userBoard::checkDirection(string &direction) {
    bool check;
    string orientation = translateDirection(direction);
    if(orientation == "down" || orientation == "across"){
        check = true; //direction is valid
    }
    else{
        check = false; //direction is not valid
    }
    return check;
}

//check the location input based on size of ship and direction, direction will be valid and coordinates will be valid
//true if the ship location fits the ship size and false if it doesn't
bool userBoard::checkShipLocation(int shipSize, string &direction, string &startCoordinates) {
    string orientation = translateDirection(direction);
    strikeLocation info = coordinateInfo(startCoordinates);
    bool check = false;
    if (orientation == "down"){ //need to check the row part of the start coordinates
        if(shipSize == 5){ //carrier
            if (info.letterRow > 6){
                check = false; // a size 5 ship can not start in row G and go down
            }else{
                check = true; //ship fits properly going up and down
            }
        }
        else if(shipSize == 4){ //battleship
            if (info.letterRow > 7){
                check = false; // a size 4 ship can not start in row H and go down
            }else{
                check = true; //ship fits properly going up and down
            }
        }
        else if(shipSize == 3){ //cruiser and submarine
            if (info.letterRow > 8){
                check = false; // a size 3 ship can not start in row I and go down
            }else{
                check = true; //ship fits properly going up and down
            }
        }
        else{ //ship size is 2 -> the destroyer
            if (info.letterRow > 9){
                check = false; // a size 2 ship can not start in row J and go down
            }else{
                check = true; //ship fits properly going up and down
            }
        }
    }
    else if(orientation == "across"){ //need to check the column part of the coordinates
        if(shipSize == 5){ //carrier
            if (info.numberCol > 6){
                check = false; // a size 5 ship can not start in row 7 and go right
            }else{
                check = true; //ship fits properly going across
            }
        }
        else if(shipSize == 4){ //battleship
            if (info.numberCol > 7){
                check = false; // a size 4 ship can not start in col 8 and go right
            }else{
                check = true; //ship fits properly going across
            }
        }
        else if(shipSize == 3){ //cruiser and submarine
            if (info.numberCol > 8){
                check = false; // a size 3 ship can not start in row 9 and go right
            }else{
                check = true; //ship fits properly going across
            }
        }
        else{ //ship size is 2 -> the destroyer
            if (info.numberCol > 9){
                check = false; // a size 2 ship can not start in column 10 and go right
            }else{
                check = true; //ship fits properly going across
            }
        }
    }
    return check;
}

//check if the user input for ship coordinates is valid or not, return true if so and false if not
bool userBoard::checkCoordinates(string &startCoordinates) {
    translateCoordinates(startCoordinates); //translate the coordinates into a readable row and column string
    int commaIndex;
    int digitCount = 0; //count the number of digits present in the column part of the coordinates
    bool temp = false; //storage for if the coordinates are valid
    if(startCoordinates == "Not a valid coordinate"){ //a false case from the translate function
        temp = false; //not valid;
    }
    else{
        commaIndex = startCoordinates.find(',');
        for(int i = commaIndex; i < startCoordinates.size(); i++) {
            if (isdigit(startCoordinates[i])) {
                digitCount += 1; //count the number of digits in the column portion of the coordinates
            }
            if (digitCount <= 2) {
                //check for extra characters in user input coordinates
                if (i != commaIndex && (ispunct(startCoordinates[i]) || isalpha(startCoordinates[i]))) {
                    temp = false; //not valid
                    break; //break because user input is for sure incorrect
                }
                if (commaIndex == startCoordinates.size() - 2) {//means column entry is single digit
                    if (i == commaIndex + 1 && startCoordinates[i] != '0') {
                        temp = true; //valid
                    }
                } else if (i == startCoordinates.size() - 1) {
                    //column entry is double digit, 10 is only valid
                    if (startCoordinates[i] == '0' && startCoordinates[i - 1] == '1') {
                        temp = true; //valid
                    }
                }
            }
        }
    }
    return temp;
}
//convert coordinates from "1,10" and return in a location struct
strikeLocation userBoard::coordinateInfo(string &startCoordinates) {
    strikeLocation info;
    string row;
    string column;
    int rowNum;
    int colNum;
    int commaIndex = startCoordinates.find(','); //row and column is separated by a comma
    //get row number
    for(int i = 0; i < commaIndex; i++){
        row += startCoordinates[i];
    }
    //get column number
    for(int i = commaIndex + 1; i < startCoordinates.size(); i++){
        column += startCoordinates[i];
    }
    //convert string to an integer to help update the made guesses vector
    rowNum = stoi(row);
    colNum = stoi(column);
    info.letterRow = rowNum;
    info.numberCol = colNum;
    return info;
}

//translate the user input for the ship coordinates
string userBoard::translateCoordinates(string &startCoordinates) {
    struct header { //header of the board
        char letter;
        int number;
    };
    //build a vector to compare the guess Letter to and then translate it to a number
    vector<header> translate;
    header info;
    char alpha = 'A';
    char firstLetter = toupper(startCoordinates[0]); //get the letter of the input, guards against lower case inputs
    for(int i = 0; i < 10; i++){
        info.letter = alpha;
        info.number = i + 1;
        translate.push_back(info);
        alpha++;
    }
    //check to see if the user input letter is a valid input and if so return the corresponding matrix value
    string numTrans;
    bool count = false;
    for(int i = 0; i < translate.size(); i++ ){
        if(translate.at(i).letter == firstLetter) {
            startCoordinates.erase(startCoordinates.begin());//erase the letter for replacement
            numTrans = to_string(translate.at(i).number);//number to replace the input location letter
            numTrans += "," + startCoordinates; //add to temp string
            startCoordinates = numTrans; //update guess
            count = true; //count for a correct letter entry
        }
    }
    if (!count){ //if the user letter was not a valid input then change the coordinates to not valid
        startCoordinates = "Not a valid coordinate";
    }
    return startCoordinates;
}

//function to translate the direction input for each ship
string userBoard::translateDirection(string &direction) {
    string orientation;
    if(direction == "V"){
        orientation = "down";
    }
    else if(direction == ">"){
        orientation = "across";
    }
    else{
        orientation = "Not a valid direction";
    }
    return orientation;
}

//convert the column number back to a letter for the purpose of display
string userBoard::rowNumConvert(int rowNumber) {
    string letter;
    struct header { //header of the board
        char letter;
        int number;
    };
    //comparison vector
    header info;
    vector<header> translate;
    char alpha = 'A';
    for(int i = 0; i < 10; i++){
        info.letter = alpha;
        info.number = i + 1;
        translate.push_back(info);
        alpha++;
    }
    for(int i = 0; i < 10; i++){
        if(translate.at(i).number == rowNumber){
            letter = translate.at(i).letter;
        }
    }
    return letter;
}

string userBoard::getFileName() {
    srand(time(0)); //unique seed
    int inputFileNum = rand() % 3 + 1; //random number between 1 and 3
    string fileName;
    if (inputFileNum == 1){
        fileName = "computer_gameV1.txt";
    }
    else if (inputFileNum == 2){
        fileName = "computer_gameV2.txt";
    }
    else{
        fileName = "computer_gameV3.txt";
    }
    return fileName;
}

//initial ship placement statements
void userBoard::printPlacementStatements(struct shipLocation &ship, string &orientation, string &startCoordinates) {
    cout << "Place your " << ship.name << " ship which is " << ship.shipSize << " spaces big." << endl;
    cout << "Enter desired orientation." << endl;
    cout << "For Down enter: V [upperCase v] || For Across (going right) enter: > [shift .]" << endl;
    cout << "Enter Orientation: ";
    cin >> orientation;
    cout << "-" << setfill('-') << setw(25) << "-" << setfill(' ') << endl;
    cout << "Given your desired orientation." << endl;
    cout << "Enter the starting coordinates of your ship" << endl;
    cout << "Example (orientation: down | starting coordinates: A7 | ship size: 3)" << endl;
    cout << "Will be placed at A7, B7, C7" << endl;
    cout << "Enter starting coordinate (Ex: A10): ";
    cin >> startCoordinates;
}

//function for printing the opponent board
void userBoard::printBoard() {
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

//a function that updates the board with the computer attacks, "X" if hit, "O" if miss
int userBoard::updateUserBoard(strikeLocation &strikeInfo, int &opponentHitCounter) {
    int strikeRow = strikeInfo.letterRow;
    int strikeCol = strikeInfo.numberCol;
    bool tempHit = false;

    cout << "Your Battleship Board" << endl;
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    //check every ship location to see if the guessed location is a hit
    for(int i = 0; i < _carrierShip.shipSize; i++) {
        if ( i < 2){ //check destroyer location
            if(_destroyer.coordinates.at(i).letterRow == strikeRow
               && _destroyer.coordinates.at(i).numberCol == strikeCol){
                tempHit = true;
                _destroyer.hits++; //add a hit to the opponent's destroyer
                opponentHitCounter += 1; //add a hit to the hit counter
                _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
                break; //break for loop because there can only be one hit
            }
        }
        if (i < 3){ //check cruiser and submarine location
            if(_cruiser.coordinates.at(i).letterRow == strikeRow
               && _cruiser.coordinates.at(i).numberCol == strikeCol){
                tempHit = true;
                _cruiser.hits++; //add a hit to the opponent's cruiser
                opponentHitCounter += 1; //add a hit to the hit counter
                _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
                break;
            }
            if(_submarine.coordinates.at(i).letterRow == strikeRow
               && _submarine.coordinates.at(i).numberCol == strikeCol){
                tempHit = true;
                _submarine.hits++; //add a hit to the opponent's submarine
                opponentHitCounter += 1; //add a hit to the hit counter
                _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
                break;
            }
        }
        if (i < 4){ //check battleship location
            if(_battleShip.coordinates.at(i).letterRow == strikeRow
               && _battleShip.coordinates.at(i).numberCol == strikeCol){
                tempHit = true;
                _battleShip.hits++; //add a hit to the opponent's battleship
                opponentHitCounter += 1; //add a hit to the hit counter
                _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
                break;
            }
        }
        //check carrierShip location
        if(_carrierShip.coordinates.at(i).letterRow == strikeRow
           && _carrierShip.coordinates.at(i).numberCol == strikeCol){
            tempHit = true;
            _carrierShip.hits++; //add a hit to the opponent's carrier
            opponentHitCounter += 1; //add a hit to the hit counter
            _board[strikeRow][strikeCol]= "X"; //replace location with an 'X'
            break;
        }
    }
    if(!tempHit){ //if there was no hit found
        _board[strikeRow][strikeCol] = "O"; //replace location with an 'O'
    }
    printBoard(); //update board by printing it
    return opponentHitCounter; // if there are 17 hits then the opponent has won
}

void userBoard::hitMissSunk(int &opponentHitMissVariable, int &opponentHitCounter) {
    if(opponentHitCounter > opponentHitMissVariable){
        cout << "Computer's coordinates were a HIT!" << endl;
    }
    else{
        cout << "Computer's coordinates were a MISS" << endl;
    }
    if(_carrierShip.hits == 5){
        cout<< "The computer sunk your " << _carrierShip.name << " ship! :(" << endl;
        _carrierShip.hits++; //update so this statement won't print again
    }
    else if(_battleShip.hits == 4){
        cout<< "The computer sunk your " << _battleShip.name << "! :(" << endl;
        _battleShip.hits++; //update so this statement won't print again
    }
    else if(_cruiser.hits == 3){
        cout<< "The computer sunk your " << _cruiser.name << " ship! :(" << endl;
        _cruiser.hits++; //update so this statement won't print again
    }
    else if(_submarine.hits == 3){
        cout<< "The computer sunk your " << _submarine.name << "! :(" << endl;
        _submarine.hits++; //update so this statement won't print again
    }
    else if(_destroyer.hits == 2){
        cout<< "The computer sunk your " << _destroyer.name << "! :(" << endl;
        _destroyer.hits++; //update so this statement won't print again
    }
}

//for the initial display and ship location initialization
void userBoard::displayUpdatedBoard() {
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    cout << "Your BattleShip Board" << endl;
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
    printBoard();
    cout << "-" << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
}