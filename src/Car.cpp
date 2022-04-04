#include <iostream>
#include "Car.h"


Car::Car(uint16_t spd, uint16_t pos, uint16_t max_spd, uint16_t rdLngth)
{
    setCar(spd, pos, max_spd, rdLngth);
}

Car::~Car(){}

void Car::setCar(uint16_t spd, uint16_t pos, uint16_t max_spd, uint16_t rdLngth)
{
    speed      = spd;
    position   = pos;
    maxSpeed   = max_spd;
    roadLength = rdLngth;
    previousPosition = pos;
}

void Car::setGap()
{
    if (next->position - position < 0)
    {
        gap = next->position - position + roadLength - 1;
    }
    else
    {
        gap = next->position - position - 1;
    }
}

void Car::brr()
{
    std::cout << "Car go brr" << std::endl;
}

