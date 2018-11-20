#ifndef BATTERY_H
#define BATTERY_H

#include "rostypes.hpp"
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>

#define PRINT_BATTERY 0

class Battery
{
    public:
        Battery(int rate, ros::NodeHandle *nh);
        float getBattery();
    private:
        void callbackVoltage(const std_msgs::Float64 msg);
        void callbackState(const std_msgs::Float32 msg);
        void callbackRecharge(const std_msgs::Int8 msg);
        ros::Rate *loop_rate;
        ros::Subscriber state_sub;
        ros::Subscriber voltage_sub;
        ros::Subscriber recharge_sub;
        float voltage, state;
        int recharge;
};

float Battery::getBattery(){
    return voltage;
}

Battery::Battery(int rate, ros::NodeHandle *nh){
    loop_rate = new ros::Rate(rate);
    //Start node
    voltage_sub = nh->subscribe("RosAria/battery_voltage", 1, &Battery::callbackVoltage, this);
    //Não tem no P3-DX
    //state_sub = nh->subscribe("RosAria/battery_state_of_charge", 1, &Battery::callbackState, this);
    //recharge_sub = nh->subscribe("RosAria/battery_recharge_state", 1, &Battery::callbackRecharge, this);
}

void Battery::callbackVoltage(const std_msgs::Float64 msg){
    voltage = msg.data;
#if PRINT_BATTERY
    std::cout << "Voltage: " << voltage << std::endl;
#endif
 //   loop_rate->sleep();
}

void Battery::callbackState(const std_msgs::Float32 msg){
    state = msg.data;
#if PRINT_BATTERY
    std::cout << "State of Charge: " << state << std::endl;
#endif   
  //  loop_rate->sleep();
}

void Battery::callbackRecharge(const std_msgs::Int8 msg){
    recharge = msg.data;
#if PRINT_BATTERY
    std::cout << "Recharge: " << recharge << std::endl;
#endif
  //  loop_rate->sleep();
}

#endif
