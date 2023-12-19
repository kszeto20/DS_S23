// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================



#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>


#include "traincar.h"
#include "traincar_prototypes.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

using std::cout; using std::endl;

// function - given a train = update the corresponding stats into the given parameters;
void TotalWeightAndCountCars(TrainCar* &train, int& tweight, int& nEng, int& nFreight, int& nPass, int& nDine, int& nSleep) {
    // set everything to 0 to prevent unitialized issues
    tweight = 0;
    nEng = 0;
    nFreight = 0;
    nPass = 0;
    nDine = 0;
    nSleep = 0;

    if (train != NULL) {
        TrainCar* temp = train;
        while (temp != NULL) { // while there are train cars left
            TrainCar tCar = *temp;
            if (tCar.isEngine()) { tweight += tCar.getWeight(); nEng += 1; }
            else if (tCar.isFreightCar()) { tweight += tCar.getWeight(); nFreight += 1; }
            else if (tCar.isPassengerCar()) { tweight += tCar.getWeight(); nPass += 1; }
            else if (tCar.isDiningCar()) { tweight += tCar.getWeight(); nDine += 1; }
            else if (tCar.isSleepingCar()) { tweight += tCar.getWeight(); nSleep += 1; }

            temp = temp->next;
        }
    }
}

// function given an existing train, add toAdd TrainCar to the list at the back
void PushBack(TrainCar* &train, TrainCar* toAdd) {
    if (train == NULL) { // if no elements - list becomes the element with NULL prev and next
        train = toAdd;
        train->next = NULL;
        train->prev = NULL;
    }
    else { // there are already elements in the list
        TrainCar* temp = train;
        while (temp->next != nullptr) { // loop to the end
            temp = temp->next;            
        }
        temp->next = toAdd; // last element next refers to toAdd
        toAdd->prev = temp; // toAdd prev refers to last element
        toAdd->next = NULL; // toAdd next = NULL because it is now the end of train
    }

}

// function given an existing train, add toAdd TrainCar to front of the list
void PushFront(TrainCar* &train, TrainCar * toAdd) {
    if (train == NULL) { // if no elements - list becomes the element with NULL prev and next
        train = toAdd;
        train->next = NULL;
        train->prev = NULL;
    }
    else { // there are already elements 
        train->prev = toAdd; // first element refers to toAdd
        toAdd->next = train; // toadd next refers to first element
        toAdd->prev = NULL; // toADD prev = NULL
        train = toAdd;
    }
}
 
// function delete all cars in the given train
void DeleteAllCars(TrainCar* &train) {
    if (train == NULL) { 
    }
    else { // if there are cars in the train
        while(train != NULL) {
            TrainCar * temp = train;
            train = temp->next; // move train forward
            temp->prev = nullptr; 
            delete temp; // delete temp node
        }
    }
}

// function get speed of the train
float CalculateSpeed(TrainCar* &train) {
    int tweight, nEng, nFreight, nPass, nDine, nSleep;
    TotalWeightAndCountCars(train, tweight, nEng, nFreight, nPass, nDine, nSleep); // get attributes of the train

    float horseP = nEng * 3000;
    float toRet = (horseP * 550 * 3600)/ ((20/0.01) * (0.02) * 5280 * tweight); // use formula to figure it out
    return toRet;

}

// helper function for finding dining car the the left
float d_stepLeft (TrainCar* &train) {
    float counter = 0;
    TrainCar * temp = train;

    while (temp != NULL) {
        TrainCar toCheck = *temp;
        if (toCheck.isEngine() || toCheck.isFreightCar()) { // if we hit a freight/engine car before we find a dining car
            return -1; // path is unviable
        }
        else {
            if (toCheck.isDiningCar()) { // if we find dining car, return counter
                return counter;
            }
            else { // increment counter + keep moving to the left
                counter++;
                temp = temp->prev;        
            }
        }        
    }

    return -1; // if dining car is never found return -1 to signal unviability

}

// helper function for finding dining car to the right - code is exactly the same as d_stepLeft but instead we step right from the given train node
float d_stepRight (TrainCar* &train) {
    float counter = 0;
    TrainCar * temp = train;

    while (temp != NULL) {
        
        TrainCar toCheck = *temp;
        if (toCheck.isEngine() || toCheck.isFreightCar()) {
            return -1;
        }
        else {            
            if (toCheck.isDiningCar()) { // if dining car is ever found, return
                return counter;
            }
            else { // else move through list + increment counter
                counter++;
                temp = temp->next;                
            }
        }
    }
    return -1; // if never found just return -1
}

// function find average distance
float AverageDistanceToDiningCar(TrainCar* &train) {
    float totalC = 0;
    float pCount = 0;
    TrainCar * temp = train;
    while (temp != NULL) {
        TrainCar toCheck = *temp;
        if (toCheck.isPassengerCar()) { // if it is a passenger 
            pCount++;
            float rCount = d_stepRight(temp); // step left
            float lCount = d_stepLeft(temp); // step right 

            if (rCount < 1 && lCount < 1) { // if left and right is not feasible return -1
                return -1;
            }
            else if (rCount < 1) {
                totalC += lCount; // add the one that is not negative

            }
            else if (lCount < 1) {
                totalC += rCount; // add the one that is not negative
            }
            else { // add the smaller of the two results 
                if (rCount < lCount) {
                    totalC += rCount;
                }
                else if (lCount < rCount) {
                    totalC += lCount;
                }
            }
        }
        temp = temp->next; // advance temp
    }
    return totalC / pCount; // return average
}

// helping function check for engine on the left
int s_stepLeft(TrainCar* &train) {
    int counter = 0;
    TrainCar * temp = train;

    while (temp != NULL) { // while not at the left end
        TrainCar toCheck = *temp;
        if (toCheck.isEngine()) { // if engine is  found return counter
            return counter;
        }
        counter++; // else increment counter + move temp forward
        temp = temp->prev;
    }

    return -1; // if engine is never found return -1 for unviable path
    
}

// helping function check for engine on the right 
int s_stepRight(TrainCar* &train) {
    int counter = 0;
    TrainCar * temp = train;

    while (temp != NULL) { // while not at right end 
        TrainCar toCheck = *temp;
        if (toCheck.isEngine()) { // if engine is found return counter
            return counter;
        }
        counter++; // else increment counter + move temp forward
        temp = temp->next;
    }

    return -1; // return to signal no engine on that side;

}

int ClosestEngineToSleeperCar(TrainCar * &train) {
    int least = 500000;
    TrainCar * temp = train;
    while (temp != NULL) { // loop through all cars
        TrainCar toCheck = *temp;
        if (toCheck.isSleepingCar()) {  // if sleeping car is found
            
            int rCount = s_stepRight(temp); // step to the left
            int lCount = s_stepLeft(temp); // step to the right

            if (rCount < 1 && lCount < 1) { // if both are not found continue
                continue;
            }
            else {
                if (rCount < 1) { // if left side found + less than is lest than original least - update
                    if (lCount < least) {
                        least = lCount;
                    }
                }
                else if (lCount < 1) { // if right side found + less than is lest than original least - update
                    if (rCount < least) {
                        least = rCount;
                    }
                }
                else {
                    if (lCount < rCount) { // if left side and right size found -- update least with whatever is less
                        if (lCount < least) {
                            least = lCount;
                        }
                    }
                    else if (rCount < lCount) {
                        if (rCount < least) {
                            least = rCount;
                        }
                    }
                }
            }
        }
        temp = temp->next; // advance
    }
    return least;

}

// function repackage freights
std::vector<TrainCar*> ShipFreight(TrainCar* &engines, TrainCar* &freights, float mSpeed, int maxC) {
    std::vector<TrainCar*> toRet; // vector to return 
    if (engines == NULL || freights == NULL || maxC < 1) { // make sure there are engines and freights to add
        return toRet;
    }
    
    float enginesUsed = 0;
    int totalAdded = 0;

    float weightsAvail = 0; // weight not yet occupied (calculated according to # of engines + formula)

    TrainCar * trainHead = nullptr; // train to add to
    
    while (freights != NULL) { // while there are still freights to be added
        float weightC = freights->getWeight(); // get the weight
        if (weightsAvail - weightC < 0) { // if the weight is more than the possible pounds to add
            
            if (engines == NULL) { // check if there are more engines to add
                break;
            }
            else {
                if (maxC - totalAdded >= 2) { // if there is space to add more engines + space to add another freight
                    TrainCar* temp = engines; // grab next engine
                    // update engines list
                    engines = engines->next;
                    if (engines != NULL) {
                        engines->prev = NULL;
                    }
                    // update amount of engines used, amount of cars added, weight available
                    enginesUsed++;
                    totalAdded += 2;
                    weightsAvail = ((enginesUsed * 3000 * 550 * 3600) / ((20/0.01) * 0.02 * 5280)) / mSpeed;
                    weightsAvail -= (enginesUsed * 150);
                    PushBack(trainHead, temp);
                }
                else { // if there is no space - push up the train + create new one
                    toRet.push_back(trainHead);
                    // reset all counters
                    totalAdded = 0;
                    enginesUsed = 0;
                    weightsAvail = 0;
                    trainHead = nullptr;
                }

            }
        }
        else { // space to add the freight
            if (totalAdded < maxC) { // if we're not at the max of the allowed cars per train
                TrainCar* temp = freights; // grab the next freight car
                // update freight list
                freights = freights->next;
                if (freights != NULL) {
                    freights->prev = NULL;
                }
                // added it to the existing train
                PushBack(trainHead, temp);
                weightsAvail -= weightC; // update counters
                totalAdded++;
            }
            else { // at the max allowed
                // push up the train + reset counters
                toRet.push_back(trainHead);
                enginesUsed = 0;
                totalAdded = 0;
                weightsAvail = 0;
                trainHead = nullptr;
            }   
        }
    }
    // if there is still freights left in the final train without being added
    if (trainHead != NULL) {
        toRet.push_back(trainHead);
        trainHead = nullptr;
    }

    return toRet; // return list of trains
}

// counter to find the total number of cars in the train
int totalCars (TrainCar * &train) {
    TrainCar * temp = train;
    int counter = 0;
    while (temp!=NULL) {
        counter++;
        temp = temp->next;
    }
    return counter;
}

// seperate the cars into 2 trains of equal-ish speeds
void Separate(TrainCar * &train, TrainCar* &first, TrainCar* &second) {
    first = nullptr;
    second = nullptr;

    int totalC = totalCars(train); // number of cars in the train
    TrainCar* firstE = nullptr; // holder for first engine 
    TrainCar* secondE = nullptr; // holder for second engine

    int half = totalC / 2; // first half amount
    int shalf = totalC - half; // second half amount 


    int leftCount = 0; // count of how many engines is on left
    int rightCount = 0; // count of how many engines is on right
    int atC = 0; // count for where I'm at in the list

    
    TrainCar * temp = train;
    while (temp != NULL) { // while I'm not at the end
        if (temp->isEngine()) { // if engine
            // add to counter of engines (left/right)
            if (atC < half) {
                leftCount++;
            }
            else {
                rightCount++;
            }

            // fix left and right pointers
            if (firstE == NULL) {
                firstE = temp;
            }
            else if (secondE == NULL) {
                secondE = temp;
            }
        }
        atC++;
        temp = temp->next; // move temp
    }
    
    if (leftCount != rightCount) {
        if (leftCount < rightCount) { // more engines on the right
            // remove the first engine
            firstE->prev->next = firstE->next;
            firstE->next->prev = firstE->prev;
            
            first = train;
            second = nullptr;

            int done = 0;

            TrainCar * prev = NULL;
            TrainCar* curr = train;

            while (curr != NULL) {
                if(totalC % 2 == 1){ // if there is an odd number of cars
                    if (done == (shalf - 1)) { // loop upto half - 1
                        
                        curr->prev = NULL;
                        prev->next = NULL;
                        second = curr; // separate the train and set the back half = to second
                    }
                    done++; // update
                    prev = curr;
                    curr = curr->next;
                } 
                else {
                   if (done == (shalf - 1)) { // loop upto half -1 
                        curr->prev = NULL;
                        prev->next = NULL;
                        second = curr; // seperate the train and set the back hald = to second
                    }
                    done++; // update 
                    prev = curr;
                    curr = curr->next;
                }
            }
            PushBack(first, firstE); // push back the first engine to the end of first
        }
        else { // more train engines on the left 
            // remove the second engine
            secondE->prev->next = secondE->next;
            secondE->next->prev = secondE->prev;

            first = train;
            second = nullptr;

            int done = 0;

            TrainCar * prev = NULL;
            TrainCar* curr = train;

            while (curr != NULL) {
                if(totalC % 2 == 1) { // if there are odd number of cars
                    if (done == shalf - 1) { // loop up to half - 1
                    curr->prev = NULL;
                    prev->next = NULL;
                    second = curr; // seperate at the middle + set back half to the second
                }
                done++;
                prev = curr; // update 
                curr = curr->next;
                }
                else {
                    if (done == shalf) { // loop upto exactly half
                        curr->prev = NULL;
                        prev->next = NULL;
                        second = curr; // separate at the middle + set remaining to second
                    }
                    done++;
                    prev = curr;
                    curr = curr->next; // update
                }
            }
            PushFront(second, secondE); // add second engine to begining of second
        }

    }
    else {
        first = train;
        second = nullptr;

        int done = 0;

        TrainCar * prev = NULL;
        TrainCar* curr = train;

        while (curr != NULL) {
            if (done == shalf - 1) { // loop up to half 
                
                curr->prev = NULL;
                prev->next = NULL;
                second = curr; // separate 
            }
            done++;
            prev = curr;
            curr = curr->next;
        }

    }

    train = nullptr; // set the orig to null
}
