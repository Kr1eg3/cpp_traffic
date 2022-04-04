#include <iostream>
#include <SNFS.h>
#include <stdlib.h>

SNFS::SNFS(double r_q, double r_r, double r_p)
{
    setSNFS(r_q, r_r, r_p);
}

SNFS::~SNFS(){}

void SNFS::setSNFS(double r_q, double r_r, double r_p)
{
    q = r_q;
    r = r_r;
    p = r_p;
}

double SNFS::randZeroToOne()
{
    return rand() / (RAND_MAX + 1.);
}

void SNFS::setS(Car* car)
{
    double sProb = r;
    double randomNumber = randZeroToOne();
 
    if (randomNumber < sProb)
    {
        car->s = car->S;
    }
    else
    {
        car->s = 1;
    }    
}

// ! Done
void SNFS::acceleration(Car* car)
{   
    uint16_t currentSpeed = car->speed;
    currentSpeed++;
    car->speed = std::min(car->maxSpeed, currentSpeed);
}

// ! Done
void SNFS::slowToStart(Car* car)
{
    double randomNumber = randZeroToOne();
    double slowToStartProb = q;
    if (randomNumber < slowToStartProb)
    {
        uint16_t one              = 1;
        uint16_t carS             = car->s;
        uint16_t currentSpeed     = car->speed;
        uint16_t prevCarPosition  = car->previousPosition;
        uint16_t prevScarPosition = car->snext->previousPosition;
        uint16_t tmpValue = prevScarPosition - prevCarPosition - carS;

        car->speed = std::min(currentSpeed, tmpValue);
    }
}

// ! Done
void SNFS::quickStart(Car* car)
{   
    uint16_t one              = 1;
    uint16_t carS             = car->s;
    uint16_t currentSpeed     = car->speed;
    uint16_t currentPosition  = car->position;
    uint16_t scarPosition     = car->snext->position;
    uint16_t tmpValue = scarPosition - currentPosition - carS;

    car->speed = std::min(currentSpeed, tmpValue);
}

// ! Done
void SNFS::randomBrake(Car* car)
{
    double randomNumber = randZeroToOne();
    double randomBrakeProb = p;
    if (randomNumber < (1 - randomBrakeProb))
    {
        uint16_t zero             = 0;
        uint16_t one              = 1;
        uint16_t currentSpeed     = car->speed;
        currentSpeed--;

        car->speed = std::max(zero, currentSpeed);
    }
}

// ! Done
void SNFS::avoidCollision(Car* car)
{   
    uint16_t one              = 1;
    uint16_t currentSpeed     = car->speed;
    uint16_t currentPosition  = car->position;
    uint16_t nextCarSpeed     = car->next->speed;
    uint16_t nextCarPosition  = car->next->position;
    uint16_t tmpValue = nextCarPosition - currentPosition - one + nextCarSpeed;

    car->speed = std::min(currentSpeed, tmpValue);
} 