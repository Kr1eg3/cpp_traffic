#include <iostream>
#include "Road.h"
#include "Car.h"
#include "SNFS.h"


RoadLane::RoadLane(SNFS* rl, uint16_t rd_lngth)
{
    setRoadLane(rl, rd_lngth);
}

RoadLane::~RoadLane(){}

void RoadLane::setRoadLane(SNFS* rl, uint16_t rd_lngth)
{
    rule = rl;
    roadLenght = rd_lngth;
    head = nullptr;
    tail = nullptr;
    
}

void RoadLane::addCar(uint16_t carSpeed, uint16_t carPosition, uint16_t maxCarSpeed, 
                      uint16_t roadLength)
{
    Car* temp = new Car(carSpeed, carPosition, maxCarSpeed, roadLength);
    temp->next = nullptr;
    temp->prev = nullptr;
    temp->snext = nullptr;

    // Если в списке нет "головы", тогда ты единственный (и "голова" и "хвост")
    if (head == nullptr)
    {
        head = temp;
        tail = temp;
        temp->id = 1;
    }
    // В ином случае:
    else
    {   
        temp->id = (tail->id) + 1;
        // У текущего "хвоста" ты становишься следующей машиной
        tail->next = temp;
        // Машина едущая позади - текущий "хвост"
        temp->prev = tail;
        // В случае, если у "хвоста" нет машины позади, то вы вдвоем на линии - вы соседи друг друга
        if (tail->prev == nullptr)
        {
            tail->prev = temp;
            temp->next = tail;
        }
        // А если она есть, то ты едешь позади "головы", а она впереди тебя
        else
        {
           head->prev = temp;
           temp->next = head; 
        }
        // Ты становишься "хвостом"
        tail = temp;
    }
}


void RoadLane::printLog(Car* currentCar)
{
    std::cout << "Car id = "         << currentCar->id              << "\t"
              << "Car speed = "      << currentCar->speed           << "\t"
              << "Car position = "   << currentCar->position        << "\t"
              << "Nxt car id = "     << currentCar->next->id        << "\t"
              << "Prev car id = "    << currentCar->prev->id        << "\t"
              << "car S value = "    << currentCar->s               << "\t"
              << "Gap param = "      << currentCar->gap             << "\n";
}

void RoadLane::printLane()
{
    Car* current = head;
    printLog(current);
    current = current->next;

    while (current != head)
    {
        printLog(current);
        current = current->next;
    }
}

std::vector<int> RoadLane::getRoadVector()
{
    std::vector<int> RoadVec(roadLenght, 0);
    Car* current = head;
    RoadVec[current->position] = current->id;
    current = current->next;

    while (current != head)
    {
        RoadVec[current->position] = current->id;
        current = current->next;
    }

    return RoadVec;
}

void RoadLane::evalS()
{
    Car* current = head;
    rule->setS(current);
    current = current->next;

    while (current != head)
    {
        rule->setS(current);
        current = current->next;
    }
}

void RoadLane::setSN()
{
    Car* current = head;
    if (current->s == 1)
    {
        current->snext = current->next;
    }
    else
    {
        current->snext = current->next->next;
    }
    current = current->next;

    while (current != head)
        {
        if (current->s == 1)
        {
            current->snext = current->next;
        }
        else
        {
            current->snext = current->next->next;
        }
        current = current->next;
    }
}

void RoadLane::evalGap()
{
    Car* current = head;
    current->setGap();
    current = current->next;

    while (current != head)
    {
        current->setGap();
        current = current->next;
    } 
}

void RoadLane::evalAcc()
{
    Car* current = head;
    rule->acceleration(current);
    current = current->next;

    while (current != head)
    {
        rule->acceleration(current);
        current = current->next;
    }  
}

void RoadLane::evalSlowTS()
{
    Car* current = head;
    rule->slowToStart(current);
    current = current->next;

    while (current != head)
    {
        rule->slowToStart(current);
        current = current->next;
    }  
}

void RoadLane::evalQuickS()
{
    Car* current = head;
    rule->quickStart(current);
    current = current->next;

    while (current != head)
    {
        rule->quickStart(current);
        current = current->next;
    }  
}

void RoadLane::evalRandB()
{
    Car* current = head;
    rule->randomBrake(current);
    current = current->next;

    while (current != head)
    {
        rule->randomBrake(current);
        current = current->next;
    }  
}

void RoadLane::evalAvoidC()
{
    Car* current = head;
    rule->avoidCollision(current);
    current = current->next;

    while (current != head)
    {
        rule->avoidCollision(current);
        current = current->next;
    }  
}

void RoadLane::getNewPos()
{
    Car* current = head;
    uint16_t currentSpd = current->speed;
    uint16_t currentPos = current->position;
    current->previousPosition = currentPos;
    int newPos = currentPos + currentSpd;
    if (newPos >= roadLenght)
    {
        newPos = newPos - roadLenght;
    } 
    current->position = newPos;
    current = current->next;
    
    while (current != head)
    {
        uint16_t currentSpd = current->speed;
        uint16_t currentPos = current->position;
        current->previousPosition = currentPos;
        int newPos = currentPos + currentSpd;
        if (newPos >= roadLenght)
        {
            newPos = newPos - roadLenght;
        } 
        current->position = newPos;
        current = current->next;
    } 
}

void RoadLane::evaluateRoad()
{
    // ! Get S's
    evalS();
    
    // ! set S neib's
    setSN();

    // ! Get gap's
    //evalGap();

    // ! apply #1-#5 rules
    evalAcc();
    evalSlowTS();
    //evalQuickS();
    //evalRandB();
    evalAvoidC();

    // ! change position
    getNewPos();
}

