#include <iostream>
#include <time.h>
#include <Windows.h>
#include <cmath>

//  Parameters
const int GridSize = 30;
const int BirdsNumber = 10;
const int GroupRadius = 10;

const float CohesionMultiplayer = 0.1;
const float BoidSpeed = 1;
//  -----

//birds vector: birds[index][0 - location, 1 - direction][0 - X, 1 - Y]
float birds[BirdsNumber][2][2] = {};

float localGroup[BirdsNumber][2][2] = {};
//[0 - location, 1 - direction][0 - X, 1 - Y]
float localAverage[2][2] = {};

//Generate n birds on x, y coordinates, [0] - x, [1] - y
void generateBirds(void){
    for(int i = 0; i < BirdsNumber; i++){
        birds[i][0][0] = rand() % GridSize + 1;
        birds[i][0][1] = rand() % GridSize + 1;
    }
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
        std::cout << "\x1b[106m " << "\x1b[0m";
    }
}

//Set provided coordinates to center of mass of local group
void updateCenter(float bird[2]){
    float sum[2] = {};
    int i = 0;
    for(i = 0; i < BirdsNumber; i++){
        //break if marked by negative value
        if(localGroup[i][0][0] < 0) break;
        //sum locations
        sum[0] += localGroup[i][0][0];
        sum[1] += localGroup[i][0][1];
    }
    //save to global var.
    localAverage[0][0] = sum[0] / i;
    localAverage[0][1] = (int) sum[1] / i;
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

void Cohesion(int bird_index, float multiplayer){
    //(center - boid_pos) * multiplayer
    birds[bird_index][1][0] = (localAverage[0][0] - birds[bird_index][0][0]) * multiplayer;
    birds[bird_index][1][1] = (localAverage[0][1] - birds[bird_index][0][1]) * multiplayer;
}

//displays provided bird
void markBird(float bird[2]){
    //move to bird location
    std::cout << "\x1b[" << int(bird[0]) << ";" << int(bird[1]) << "H";
    //display character, clear displaying, 41 represents colour
    std::cout << "\x1b[41m " << "\x1b[0m";
}

void updateLocation(int bird_index, float multiplayer){
    birds[bird_index][0][0] = birds[bird_index][0][0] + (birds[bird_index][1][0] * multiplayer);
    birds[bird_index][0][1] = birds[bird_index][0][1] + (birds[bird_index][1][1] * multiplayer);
}

int main(){
    srand(time(NULL));
    generateBirds();
    
    // std::cin.get();

    for(int i = 0; i < 100; i++){
        displayBirds();
        for(int k = 0; k < BirdsNumber; k++){
            //create local group
            updateLocalGroup(birds[k][0]);
            //calculate local center of mass
            updateCenter(birds[k][0]);
            //apply cohesion rule
            Cohesion(k, CohesionMultiplayer);
            //update location of bird - move by direction vector
            updateLocation(k, BoidSpeed);
        }
        Sleep(100);
    }

    
    displayLocalBirds();
    updateCenter(birds[0][0]);
    markBird(localAverage[0]);
    for(int i = 0; i < BirdsNumber; i++){
        std::cout << birds[i][1][0] << std::endl;
    }
    return 0;
}
