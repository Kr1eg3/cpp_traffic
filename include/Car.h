#pragma once
#include <iostream>

/**
 * @brief 
 *  Класс автомобиля, управляемого человеком
 *  (клеточным автоматом)
 * 
 */
class Car
{
private:
    /* private data */
public:
    // id машины
    uint16_t id;

    uint16_t gap;

    uint16_t roadLength;

    // Параметры машины
    
    // Скорость машины
    uint16_t speed;
    // Позиция машины
    uint16_t position;
    // Макс. скорость машины
    uint16_t maxSpeed;
    // Предыдущая позиция машины
    uint16_t previousPosition;


    // Параметры модели
    //=======================
    uint16_t S = 2;
    uint16_t s;

    //=======================

    // Указатели на соседей 
    class Car* next;
    class Car* prev;
    class Car* snext;

    // Список функций
    //========================================

    // Конструктор + деструктор
    Car(uint16_t, uint16_t, uint16_t, uint16_t);
    ~Car();

    // Функционал
    void setCar(uint16_t, uint16_t, uint16_t, uint16_t);
    void setGap();
    void brr();
    //========================================
};

