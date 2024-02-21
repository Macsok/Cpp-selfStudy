#include <iostream>
#include <time.h>
#include <Windows.h>
#include <cmath>

//  Parameters
const int GridSize = 30;
const int BirdsNumber = 10;
const int GroupRadius = 10;

//  -----

//birds vector: birds[index][0 - location, 1 - direction][0 - X, 1 - Y]
float birds[BirdsNumber][2][2] = {};

float localGroup[BirdsNumber][2][2] = {};

//Generate n birds on x, y coordinates, [0] - x, [1] - y
void generateBirds(void){
    for(int i = 0; i < BirdsNumber; i++){
        birds[i][0][0] = rand() % GridSize;
        birds[i][0][1] = rand() % GridSize;
    }
}

//Generate bird on random x, y coordinates
void generateBird(int* bird, int grid_size){
    bird[0] = rand() % grid_size;
    bird[1] = rand() % grid_size;
}

//Clear board then display every bird on its location
void displayBirds(void){
    //clear screen
    system("cls");
    for(int i = 0; i < BirdsNumber; i++){
        //move to bird location
        std::cout << "\x1b[" << int(birds[i][0][0]) << ";" << int(birds[i][0][1]) << "H";
        //display character, clear displaying
        std::cout << "\x1b[42m " << "\x1b[0m";
    }
}

//Show local group of birds
void displayLocalBirds(void){
    //clear screen
    //system("cls");
    for(int i = 0; i < BirdsNumber; i++){
        //break if there is no more local ones
        if(localGroup[i][0][0] < 0) break;
        //move to bird location
        std::cout << "\x1b[" << int(localGroup[i][0][0]) << ";" << int(localGroup[i][0][1]) << "H";
        //display character, clear displaying
        std::cout << "\x1b[43m " << "\x1b[0m";
    }
}

//Set provided coordinates to center of mass
void getCenter(int* direction[2]){
    int sum[2] = {};
    for(int i = 0; i < BirdsNumber; i++){
        //sum locations
        sum[0] += birds[i][0][0];
        sum[1] += birds[i][0][1];
    }
    *direction[0] = (int) sum[0] / BirdsNumber;
    *direction[1] = (int) sum[1] / BirdsNumber;
}

//Find birds close to provided one and save them in the global array
void updateLocalGroup(float bird_xy[2]){
    int k = 0;
    for(int i = 0; i < BirdsNumber; i++){
        float distance_between = pow(pow(birds[i][0][0] - bird_xy[0], 2) + pow(birds[i][0][1] - bird_xy[1], 2), 0.5);
        if(distance_between < GroupRadius){
            //add bird to local group
            localGroup[k][0][0] = birds[i][0][0];
            localGroup[k][0][1] = birds[i][0][1];
            localGroup[k][1][0] = birds[i][1][0];
            localGroup[k][1][1] = birds[i][1][1];
            //switch to next bird
            k++;
        }
    }
    //mark end of the local group
    localGroup[k][0][0] = -1;
}



int main(){
    srand(time(NULL));
    generateBirds();
    displayBirds();
    int str;
    std::cin >> str;
    updateLocalGroup(birds[0][0]);
    displayLocalBirds();
    return 0;
}