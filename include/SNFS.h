#pragma once
#include <iostream>
#include "Car.h"


/**
 * @brief 
 *  Класс правил
 *  
 * 
 */
class SNFS
{
private:
    /* data */
public:
    // Параметры правила
    double q;
    double r;
    double p;
    

    // Список функций
    // Конструктор + деструктор
    SNFS(double, double, double);
    ~SNFS();

    // Функционал
    double randZeroToOne();
    void  setSNFS(double, double, double);
    void  setS(Car* car);
    void  acceleration(Car* car);
    void  slowToStart(Car* car);
    void  quickStart(Car* car);
    void  randomBrake(Car* car);
    void  avoidCollision(Car* car);
    
};
 