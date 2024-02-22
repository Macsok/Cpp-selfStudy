#include <iostream>
#include <time.h>
#include <Windows.h>
#include <cmath>

//  Parameters
const int GridSize = 200;
const int BirdsNumber = 250;
const int GroupRadius = 10;

const float CohesionMultiplier = 0.05;

const float SeparationMultiplier = 0.2;
const float SeparateRadius = 5;
const float AvoidBorder = 3;

const float AlignmentMultiplier = 0.7;

const float goToCenterMultiplier = 0.05;
const float BoidSpeed = 7;
const float SlowDownMultiplier = 1;

//animation delay in ms
const int Delay = 0;
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
        std::cout << "\x1b[43m " << "\x1b[0m";
    }
}

//Set provided coordinates to center of mass of local group
void updateAverage(float bird[2]){
    float pos[2] = {};
    float dir[2] = {};
    int i = 0;
    for(i = 0; i < BirdsNumber; i++){
        //break if marked by negative value
        if(localGroup[i][0][0] < 0) break;
        //sum locations
        pos[0] += localGroup[i][0][0];
        pos[1] += localGroup[i][0][1];
        //sum directions
        dir[0] += localGroup[i][1][0];
        dir[1] += localGroup[i][1][1];
    }
    //save to global var.
    //position
    localAverage[0][0] = pos[0] / i;
    localAverage[0][1] = pos[1] / i;
    //direction
    localAverage[1][0] = dir[0] / i;
    localAverage[1][1] = dir[1] / i;
}

//Find birds close to provided one and save them in the global array
void updateLocalGroup(float bird_xy[2], float radius){
    int k = 0;
    for(int i = 0; i < BirdsNumber; i++){
        float distance_between = pow(pow(birds[i][0][0] - bird_xy[0], 2) + pow(birds[i][0][1] - bird_xy[1], 2), 0.5);
        if(distance_between < radius){
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

//turns direction towards local center of mass
void Cohesion(int bird_index, float multiplier){
    //(center - boid_pos) * multiplier
    birds[bird_index][1][0] = (localAverage[0][0] - birds[bird_index][0][0]) * multiplier;
    birds[bird_index][1][1] = (localAverage[0][1] - birds[bird_index][0][1]) * multiplier;
}

//steers away from close birds (from local group)
void Separation(int bird_index, float multiplier){
    //if close then vec = vec - (close_boid_location - boid_location)
    birds[bird_index][1][0] += (birds[bird_index][0][0] - localAverage[0][0]) * multiplier;
    birds[bird_index][1][1] += (birds[bird_index][0][1] - localAverage[0][1]) * multiplier;
}

void Alignment(int bird_index, float multiplier){
    //update boid direction multiplied by given number
    birds[bird_index][1][0] += localAverage[1][0] * multiplier;
    birds[bird_index][1][1] += localAverage[1][1] * multiplier;
}

//displays provided bird
void markBird(float bird[2]){
    //move to bird location
    std::cout << "\x1b[" << int(bird[0]) << ";" << int(bird[1]) << "H";
    //display character, clear displaying, 41 represents colour
    std::cout << "\x1b[41m " << "\x1b[0m";
}

//updates location by adding direction to current location
void updateLocation(int bird_index, float multiplier){
    birds[bird_index][0][0] = birds[bird_index][0][0] + (birds[bird_index][1][0] * multiplier);
    birds[bird_index][0][1] = birds[bird_index][0][1] + (birds[bird_index][1][1] * multiplier);
}

//set all directions to center of whole flock
void setDefaultDirection(float multiplier){
    //add every boid to local group
    updateLocalGroup(birds[0][0], GridSize * GridSize);
    updateAverage(birds[0][0]);
    for(int i = 0; i < BirdsNumber; i++){
        birds[i][1][0] = (localAverage[0][0] - birds[i][0][0]) * multiplier;
        birds[i][1][1] = (localAverage[0][1] - birds[i][0][1]) * multiplier;
    }
}

//keep boids in one place
void steerAwayFromBorder(int bird_index, float multiplier){
    //check borders
    if(birds[bird_index][0][0] < 1){
        birds[bird_index][1][0] += (birds[bird_index][0][0] * multiplier);
    }
    if(birds[bird_index][0][1] < 1){
        birds[bird_index][1][1] += (birds[bird_index][0][1] * multiplier);
    }

    if(birds[bird_index][0][0] > GridSize){
        birds[bird_index][1][0] -= (birds[bird_index][0][0] - GridSize) * multiplier;
    }
    if(birds[bird_index][0][1] > GridSize){
        birds[bird_index][1][1] -= (birds[bird_index][0][1] - GridSize) * multiplier;
    }
}

void resetDirection(int bird_index){
    birds[bird_index][1][0] = 0;
    birds[bird_index][1][1] = 0;
}

void symulate(bool follow = false){
    generateBirds();
    while(true){
        displayBirds();
        //slowDownBoids(SlowDownMultiplier);
        for(int k = 0; k < BirdsNumber; k++){
            //resetDirection(k);

            //create local group
            updateLocalGroup(birds[k][0], GroupRadius);

            //mark followed boids
            if(follow && k == 0){
                displayLocalBirds();
                markBird(birds[k][0]);
            }

            //calculate local center of mass
            updateAverage(birds[k][0]);
            //apply cohesion rule
            Cohesion(k, CohesionMultiplier);
            //apply alignment rule
            Alignment(k, AlignmentMultiplier);
            //update local group then apply separation rule
            updateLocalGroup(birds[k][0], SeparateRadius);
            updateAverage(birds[k][0]);
            Separation(k, SeparationMultiplier);

            steerAwayFromBorder(k, AvoidBorder);

            //update location of bird - move by direction vector
            updateLocation(k, BoidSpeed);
        }
        Sleep(Delay);
    }
}

int main(){
    srand(time(NULL));
    symulate();
    return 0;
}