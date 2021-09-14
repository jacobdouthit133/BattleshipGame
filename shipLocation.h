//
// Created by thadd on 6/24/2021.
//

#ifndef FINAL_PROJECT_SHIPLOCATION_H
#define FINAL_PROJECT_SHIPLOCATION_H
using namespace std;

struct shipLocation{
    string name;
    int shipSize;
    string identifier;
    int hits = 0;
    vector<strikeLocation> coordinates;
};
#endif //FINAL_PROJECT_SHIPLOCATION_H
