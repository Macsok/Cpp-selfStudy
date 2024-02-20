#include <iostream>
#include <time.h>
#include <cmath>

//  Parameters
const int GridSize = 400;
const int BirdsNumber = 10;

//  -----

//float board[grid_size][grid_size] = {};

//Generate n birds on x, y coordinates, [0] - x, [1] - y
void generateBirds(int* birds, int grid_size){
    for(int i = 0; i < BirdsNumber; i++){
        birds[i] = 0;
        birds[i][0] = rand() % grid_size;
        birds[i][1] = rand() % grid_size;
    }
}

//Generate bird on random x, y coordinates
void generateBird(int* bird, int grid_size){
    bird[0] = rand() % grid_size;
    bird[1] = rand() % grid_size;
}

void displayBirds(float birds[][2], int grid_size){
    for(int i = 0; i < sizeof(birds); i++){
        std::cout << "clf";
        //move to bird location
        std::cout << "\x1b[" << birds[i][0] << ";" << birds[i][1] << "H";
        //display character, clear displaying
        std::cout << "\x1b[42m " << "\x1b[0m";
    }
}

int main(){
    int birdsArray[BirdsNumber][2] = {};
    int ptr = birdsArray[0][0];
    generateBirds(ptr, GridSize);
    return 0;
}