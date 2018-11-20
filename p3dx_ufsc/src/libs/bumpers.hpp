#ifndef BUMPERS_H
#define BUMPERS_H

#include <rosaria/BumperState.h>
#include <vector>

#define PRINT_BUMPER_STATE 0

class Bumpers
{
    public:
        Bumpers(int rate, ros::NodeHandle *nh);
        std::vector <bool> getFrontBumpers();
        std::vector <bool> getRearBumpers();
    private:
        void callbackBumpers(const rosaria::BumperState &msg);
        ros::Rate *loop_rate;
        ros::Subscriber bumpers_sub;
        std::vector <bool> front_bumpers;
        std::vector <bool> rear_bumpers; 
};

Bumpers::Bumpers(int rate, ros::NodeHandle *nh){
    loop_rate = new ros::Rate(rate);

    bumpers_sub = nh->subscribe("RosAria/bumper_state", 1, &Bumpers::callbackBumpers, this);
}

std::vector <bool> Bumpers::getFrontBumpers(){
    return front_bumpers;
}

std::vector <bool> Bumpers::getRearBumpers(){
    return rear_bumpers;
}

void Bumpers::callbackBumpers(const rosaria::BumperState &msg){
    int front_size = sizeof(msg.front_bumpers) / sizeof(bool);
    int rear_size  = sizeof(msg.rear_bumpers) / sizeof(bool);
    front_bumpers.clear();
    rear_bumpers.clear();
    for (int i = 0; i < front_size; i++){
        front_bumpers.push_back(msg.front_bumpers[i]);
    }
    for (int i = 0; i < rear_size; i++){
        rear_bumpers.push_back(msg.rear_bumpers[i]);
    }

#if PRINT_BUMPER_STATE 
    std::cout << "Front Bumpers: ";
    for (int i = 0; i < front_size; i++){
        if (msg.front_bumpers[i])
            std::cout << "1, ";
        else
            std::cout << "0, ";
    }
    std::cout << std::endl; 
    
    std::cout << "Rear Bumpers:  ";
    for (int i = 0; i < rear_size; i++){
        if (msg.rear_bumpers[i])
            std::cout << "1, ";
        else
            std::cout << "0, ";
    }
    std::cout << std::endl;

#endif
    //loop_rate->sleep();
}   


#endif
