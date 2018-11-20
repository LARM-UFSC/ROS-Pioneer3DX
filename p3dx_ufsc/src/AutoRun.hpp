#ifndef AUTORUN_H
#define AUTORUN_H

#include <cmath>
#include <iostream>
#include <signal.h>
#include <std_msgs/Char.h>
#include "libs/rostypes.hpp"
#include "libs/defines_sockets.hpp"
#include "libs/bumpers.hpp"
#include "libs/sonar.hpp"
#include "libs/motors.hpp"
#include "libs/lasers.hpp"
#include "libs/pose.hpp"
#include "libs/battery.hpp"

void quit(int sig)
{
    std::cout << "Finalizando programa!" << std::endl;
    ros::shutdown();
    exit(0);
}

class AutoRun
{
    public:
        AutoRun();
        void mainLoop();
    private:
        //callbacks
        void callbackMobile(const std_msgs::Char msg);
        //Principal Node
        ros::NodeHandle nh;
        //Nodes that run togheter on the principal node
        Sonar *sonar;
        Motors *motors;
        Pose *pose;
        Lasers *lasers;
        Bumpers *bumpers;
        Battery *battery;
        //mobile sub
        ros::Subscriber mobileApp_sub;
        //Variable Infos from Nodes
        ros::Rate *loop_rate;
        std::vector < float > medicoes;  
        bool teleop;     
        float linear_vel;
        float angular_vel;
};

AutoRun::AutoRun(){
    //Initialize principal nodes
    sonar = new Sonar(25, &nh);
    motors = new Motors(25, &nh);
    pose = new Pose(&nh);
    bumpers = new Bumpers(1, &nh);
    battery = new Battery(1, &nh);
    lasers = new Lasers(1, &nh);
    //Other variables
    loop_rate = new ros::Rate(1000);
    teleop = true;
    linear_vel = 0.51;
    angular_vel = 0.51;
    //mobile sub
    mobileApp_sub = nh.subscribe("socketCom", 1, &AutoRun::callbackMobile, this);
    //Quit program
    signal(SIGINT,quit);
}

void AutoRun::callbackMobile(const std_msgs::Char msg){

    char step = msg.data;
    switch(step){
        case SINAL_ACELERAR:
            if (teleop)
                motors->setVelocity(0, linear_vel);
            break;
        case SINAL_RE:
            if (teleop)
                motors->setVelocity(0, -linear_vel);
            break;
        case SINAL_DIREITA:
            if (teleop)
                motors->setVelocity(-angular_vel, 0);
            break;
        case SINAL_ESQUERDA:
            if (teleop)
                motors->setVelocity(angular_vel, 0);
            break;
        case SINAL_PARAR:
            if (teleop)
                motors->setVelocity(0, 0);
            break;
        case SINAL_AUMLIN:
            if (teleop)
                if (linear_vel < 2)
                    linear_vel += 0.1;
            break;
        case SINAL_AUMANG:
            if (teleop)
                if (angular_vel < 2)
                    angular_vel += 0.1;
            break;
        case SINAL_DIMLIN:
            if (teleop)
                if (linear_vel > 0.1)
                    linear_vel -= 0.1;
            break;
        case SINAL_DIMANG:
            if (teleop)
                if (angular_vel > 0.1 )
                    angular_vel -= 0.1;
            break;
        case SINAL_TELEOP:
            if (teleop == true)
                teleop = false;
            else 
                teleop = true;
            break;
        default:
            break;
    }
}

void AutoRun::mainLoop(){
    float angular_vel = 0;
    float linear_vel = 0;
    int tick = -1;

    motors->enableMotors();
    loop_rate->sleep();

    for(;;) {
        if (!teleop){
            medicoes = lasers->getLasers();
            float MLS = 0, M = 0, MRS = 0;
            if (medicoes.size() >= 3){
                MLS = medicoes[0];
                M   = medicoes[1];
                MRS = medicoes[2];
            }
            if (tick < 0){
                if (MLS < 1 && MLS != 0){
                    angular_vel = 0.6666;
                    linear_vel = 0;
                    tick = 1;
                } else if (MRS < 1 && MLS != 0){
                    angular_vel = -0.6666;
                    linear_vel = 0;
                    tick = 1;
                } else if (M < 1 && M != 0){
                    angular_vel = 0.8888;
                    linear_vel = 0;
                    tick = 1;
                } else {
                    linear_vel = 0.2;
                    angular_vel = 0;
                }
            }
            tick--;
        
            motors->setVelocity(angular_vel*2.5, linear_vel*5);
        }

        loop_rate->sleep();
        ros::spinOnce(); //call the callback functions
    }
}

#endif
