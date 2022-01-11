#include <iostream>
#include <time.h>

class Car {

public:
  // Car params
  int speed;
  int position;
  int max_speed;

  int prev_speed;
  int prev_position;

  // Model params
  double q    =  0.99;
  double r    =   0.5;
  double p    =   1.0;
  double P1   = 0.999;
  double P2   =  0.99;
  double P3   =  0.98;
  double P4   =  0.01;
  int    s    =     1;
  int    S    =     2;
  int    G    =    15;
  
  // Pointers for neighbours
  class Car* next;
  class Car* prev;
  class Car* snext;
  class Car* endlane;

  // Constructor
  Car(int spd, int pstn, int mxspd)
  {
    speed = spd;
    position = pstn;
    max_speed = mxspd;

    prev_speed = 0;
    prev_position = position;
  }

  // Destructor
  ~Car(){}

  int count_gap(int road_lenght,  bool count_prev=false)
  {
    int gap;
    if (!count_prev)
    {
      gap = next -> position - position;
      if (gap < 0)
      {
        gap += road_lenght;
      }
      return gap;
    }
    else
    {
      gap = next -> prev_position - position;
      if (gap < 0)
      {
        gap += road_lenght;
      }
      return gap;
    }
  }

  int count_sgap(int road_lenght, bool count_prev=false)
  {
    int sgap;
    if (!count_prev)
    {
      sgap = next -> next -> position - position;
      if (sgap < 0)
      {
        sgap += road_lenght;
      }
      return sgap;
    }
    else
    {
      sgap = next -> next -> prev_position - prev_position;
      if (sgap < 0)
      {
        sgap += road_lenght;
      }
      return sgap;
    }
  }

   double random()
  {
    return double ((double)rand()/(double)RAND_MAX);
  }

};


class NFS
{


public:
  NFS(){}
  ~NFS(){}
  
  void acceleration(Car* car)
  {
    car -> speed = std::min(car -> max_speed, car -> speed + 1);
  }

  void slow_to_start(Car* car, int gap_prev)
  {

    car -> speed = std::min(car -> speed, gap_prev - car -> s);
  }

  void quick_start(Car* car, int gap_s)
  {
    car -> speed = std::min(car -> speed, gap_s - car -> s);
  }

  void avoid_collision(Car* car, int gap)
  {
    car -> speed = std::min(car -> speed, gap - 1 + car -> next -> speed);
  }

};

class SNFS
{
public:
  SNFS(){}
  ~SNFS(){}

  void acceleration(Car* car)
  {
    car -> speed = std::min( car -> max_speed, car -> speed + 1 );
  }

  void slow_to_start(Car* car, int road_lenght, int s)
  {
    if (s == 1)
    {
      int gap = car -> count_gap( road_lenght, true ); 
      car -> speed = std::min( car -> speed, gap - s );
    }
    else
    {
      int gap = car -> count_sgap( road_lenght, true );
      car -> speed = std::min( car -> speed, gap - s );
    }
  }

  void quick_start(Car* car, int road_lenght, int s)
  {
    if (s == 1)
    {
      int gap = car -> count_gap( road_lenght );
      car -> speed = std::min( car -> speed, gap - s );
    }
    else
    {
      int gap = car -> count_sgap( road_lenght );
      car -> speed = std::min( car -> speed, gap - s );
    }
  }
    
  void random_brake(Car* car)
  {
    //with 1-p
    car -> speed = std::max( 0, car -> speed );
  }

  void avoid_collision(Car* car, int road_lenght)
  {
    int gap = car -> count_gap( road_lenght );
    car -> speed = std::min( car -> speed, gap - 1 + car -> next -> speed );
  }
};

class RoadLane
{
public:
  int road_lenght;
  double counter = 0;
  double road_flow = 0.0;
  double avg_flow;
  
  RoadLane(int rdln)
  {
    road_lenght = rdln;

    head = nullptr;
    tail = nullptr;
  }
  
  ~RoadLane(){};

  void addCar(int speed, int position, int max_speed)
  {
    // TODO Добавить логику для s-машины
    Car* temp = new Car(speed, position, max_speed);
    temp ->  next = nullptr;
    temp ->  prev = nullptr;
    temp -> snext = nullptr;
    temp -> endlane = nullptr;

    if (head == nullptr)
    {
      head = temp;
      tail = temp;
    }
    else
    {
      tail -> endlane = temp;
      tail -> next = temp;
      temp -> prev = tail;
      temp -> next = head;
      tail = temp;
     
    }
  }

  void printLane() 
  {
    Car* current = head;

    while (current != nullptr)
    {
      std::cout << "Speed = " <<  current -> speed               << "\t"
                << "Position = " << current -> position          << "\t"
                << "Max_speed = " << current -> max_speed        << "\t"
                << "Prev_speed = " << current -> prev_speed      << "\t"
                << "Prev_position = " << current ->prev_position << "\n"; 
      current = current -> endlane;
    }
  }

  void printToFile()
  {
    // TODO
  }

  void pushCar(int speed, int position, int max_speed)
  {
    Car* new_car;
    new_car = new Car(speed, position, max_speed);

    new_car -> speed = speed;
    new_car -> next = head;

    head = new_car;
  }

  void getS()
  {
    Car* current = head;

    while (current != nullptr)
    {
      if (current -> random() < current -> r)
      {
        current -> S = 2;
      }
      else
      {
        current -> S = 1;
      }
      current = current -> endlane;
    }
  }
  
  void applyAcc(SNFS* rule)
  {
    Car* current = head;

    while (current != nullptr)
    {
      rule -> acceleration( current );
      current = current -> endlane;
    }
  }

  void applySS(SNFS* rule)
  {
    Car* current = head;

    while (current != nullptr)
    {
      if (current -> random() < current -> q)
      {
        rule -> slow_to_start( current, road_lenght, current -> S );
      }
      current = current -> endlane;
    }
  }

  void applyPQS(SNFS* rule)
  {
    Car* current = head;

    while (current != nullptr)
    {
      rule -> quick_start( current, road_lenght, current -> S );
      current = current -> endlane;
    }
  }

  void applyRB(SNFS* rule)
  {
    Car* current = head;

    while (current != nullptr)
    {
      if (current -> random() < 1 - current -> p)
      {
        rule -> random_brake( current );
      }
      current = current -> endlane;
    }
  }

  void applyCol(SNFS* rule)
  {
    Car* current = head;

    while (current != nullptr)
    {
      rule -> avoid_collision( current, road_lenght );
      current = current -> endlane;
    }
  }

  void make_step()
  {
    Car* current = head;

    while (current != nullptr)
    {
      current -> prev_position = current -> position;
      current -> position += current -> speed;
      if (current -> position >= road_lenght)
      {
        current -> position -= road_lenght;
        road_flow += 1.0;
      }
      current = current -> endlane;
    }
  }
 

  void go_rule(SNFS* rule)
  {
    getS();
    applyAcc( rule );
    applySS( rule );
    applyPQS( rule );
    applyCol( rule );
    make_step();
  }

  
private:
  Car* head;
  Car* tail;
};


int main()
{
  srand( (unsigned)time( NULL ) );
  std::cout << "Start experiment" << std::endl;
  int cars_total = 5;
  int road_lenght = 10;
  int max_speed = 2;
 
  //char buffer[0x100];
  //std::snprintf(buffer, sizeof(buffer), "results.txt"); 
  //FILE* file = fopen(buffer, "w");
  
  SNFS* rule;
  rule = new SNFS;

  RoadLane* lane_one;
  lane_one = new RoadLane(road_lenght);
  

  // Main cycle
  // for dens in range():
  //   init conf
  //   for epoch in range():
  //     do_stuff()
  //

  for (double denity = 0.0; denity < 1.0; denity += 0.1)
  {
    std::cout << denity << std::endl;
    cars_total = int(denity * road_lenght);

  }


  int Arr[10] = {0, 0, 1, 0, 1, 1, 0, 1, 0, 0};
  for (int position = 0; position < road_lenght; position++)
  {
    if (Arr[position] == 1)
    {
      lane_one -> addCar( 1, position, max_speed );
    }
  }
  
  for (int epoch = 0; epoch < 2; epoch++)
  {
    lane_one -> go_rule( rule );
    lane_one -> printLane();
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
  }
  
  lane_one -> avg_flow = lane_one -> road_flow / 2;

  //lane_one -> printLane();
  std::cout << "End experiment" << std::endl;

  //lane_one -> evaluate(road_lenght);


  return 0;
}



