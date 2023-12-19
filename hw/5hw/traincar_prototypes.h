#ifndef __trainproto_h
#define __trainproto_h

#include "traincar.h"
#include <iostream>
// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//

void TotalWeightAndCountCars(TrainCar* &train, int& tweight, int& nEng, int& nFreight, int& nPass, int& nDine, int& nSleep);
void PushBack(TrainCar* &train, TrainCar* toAdd);
void PushFront(TrainCar* &train, TrainCar * toAdd);
void DeleteAllCars(TrainCar* &train);
float CalculateSpeed(TrainCar* &train);

float AverageDistanceToDiningCar(TrainCar* &train);
float d_stepLeft (TrainCar* &train); // helper functions for finding dining - left
float d_stepRight (TrainCar* &train); // helper function for finding dining - right


int ClosestEngineToSleeperCar(TrainCar * &train);
int s_stepLeft(TrainCar* &train); // helper functions for finding sleeping - left
int s_stepLeft(TrainCar* &train); // helper functions for finding sleeping - right

std::vector<TrainCar*> ShipFreight(TrainCar* &engines, TrainCar* &freights, float mSpeed, int maxC);

int totalCars (TrainCar * &train); // finds the total amount of cars in the list
void Separate(TrainCar * &train, TrainCar* &first, TrainCar* &second);

#endif