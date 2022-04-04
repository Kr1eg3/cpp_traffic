#pragma once
#include <iostream>
#include <stdint.h>
#include <random>
#include "Car.h"
#include "SNFS.h"






/**
 * @brief 
 * 
 */
class RoadLane
{
private:
    Car* head;
    Car* tail;
public:
    // Параметры линии дороги

    // Длина дороги
    uint16_t  roadLenght;

    SNFS* rule;

    // ! Список функций
    // ! ========================================

    // Конструктор + деструктор
    RoadLane(SNFS* , uint16_t);
    ~RoadLane();

    // Функционал
    void setRoadLane(SNFS* , uint16_t);
    void addCar(uint16_t carSpeed, uint16_t carPosition, uint16_t maxCarSpeed, uint16_t roadLenght);
    std::vector<int> getRoadVector();
    void printLog(Car* currentCar);
    void printLane();
    void evalS();
    void setSN();
    void evalGap();
    void evalAcc();
    void evalSlowTS();
    void evalQuickS();
    void evalRandB();
    void evalAvoidC();
    void getNewPos();
    void evaluateRoad();
    // ! ========================================
};


