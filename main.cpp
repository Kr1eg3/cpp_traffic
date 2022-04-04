#include <iostream>
#include <fstream>
#include <stdint.h>
#include <random>
#include <iterator>
#include <time.h>
#include "Car.h"
#include "SNFS.h"
#include "Road.h"


// ! proto's
//=======================================================
// Some protoypes (if needed)


void setupRoadLane(RoadLane* p_rl, std::vector<int> roadLane);
std::vector<int> getInitVector(uint16_t roadLength, uint16_t carNumber);

//=======================================================

/*
 * @brief Main func
 *  
 * 
 * @return int 
 */
int main()
{
    std::cout << "Hello" << std::endl;
    uint16_t t_carSpeed     = 2;
    uint16_t t_carPosition  = 11;
    uint16_t t_carMaxSpeed  = 3;
    uint16_t t_roadLength   = 20;
    uint16_t t_evalTime     = 30;

    long timer  = time(NULL);
    int  stimer = (unsigned int) timer / 2;
    srand(stimer);

    std::vector<int> initLane = getInitVector(t_roadLength, 8);
    
    double q = 1.0;
    double r = 0.5; 
    double p = 1.0;

    SNFS* rule1 = new SNFS(q, r, p);
    RoadLane* testLane = new RoadLane(rule1, t_roadLength);

    setupRoadLane(testLane, initLane);

    // Main cycle
    std::fstream file;
    file.open("vector_road.txt",std::ios_base::out);
    for (int i = 0; i < t_evalTime; i++)
    {
        testLane->evaluateRoad();
        testLane->printLane();
        std::vector<int> v = testLane->getRoadVector();
        for(auto content: v)
        {
            file<<content<< " ";
        }
        file<<std::endl;
        //std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
        //std::ofstream output_file("./example.txt");
        //std::ostream_iterator<int> output_iterator(output_file);
        //std::copy(v.begin(), v.end(), output_iterator);
        //std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "==== " << "End " << i + 1 << " step" << " ====" << std::endl;
    }

    file.close();

    return 0;
}

/**
 * @brief Get the Init Vector object
 * 
 * @param roadLength 
 * @param carNumber 
 * @return std::vector<int> 
 */
std::vector<int> getInitVector(uint16_t roadLength, uint16_t carNumber)
{
    std::vector<int> initVec(roadLength - carNumber, 0);
    for (int i = 0; i < carNumber; i++)
    {
        initVec.push_back(1);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(initVec.begin(), initVec.end(), g);
    //std::copy(initVec.begin(), initVec.end(), std::ostream_iterator<int>(std::cout, " "));
    
    return initVec; 
}

/**
 * @brief Заполняет машинами дорогу
 * 
 * 
 * @param p_rl 
 * @param roadLane 
 */
void setupRoadLane(RoadLane* p_rl, std::vector<int> roadLane)
{
    for (int i = 0; i < roadLane.size(); i++)
    {
        if (roadLane[i] == 1)
        {
            //===========Start speed==Position==Max speed=====RoadL========
            p_rl->addCar(     0,         i,        3,     roadLane.size());
        }
    }
}