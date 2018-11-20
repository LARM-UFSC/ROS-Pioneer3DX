#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <sstream>
#include "libs/rostypes.hpp"
#include "libs/defines_sockets.hpp"
#include "libs/sonar.hpp"
#include "libs/lasers.hpp"
#include "libs/pose.hpp"
#include "libs/battery.hpp"
#include <iostream>
#include <math.h>

#define PRINT_SONAR 0


class Monitor
{
    public:
        Monitor();
        std::string getInfo();
    private:
        ros::NodeHandle nh;
        //Nodes that run togheter on the principal node
        Sonar *sonar; //get info about sonar
        Pose *pose; //get some info about position
        Lasers *lasers; //info about lasers
        Battery *battery; //get some info about battery

        ros::Rate *loop_rate;
};

Monitor::Monitor(){
    sonar = new Sonar(25, &nh);
    pose = new Pose(&nh);
    battery = new Battery(1, &nh);
    lasers = new Lasers(1, &nh);

    loop_rate = new ros::Rate(1000);
}

std::string Monitor::getInfo(){
    std::string info_;
    std::ostringstream ss;

    float battery_ = battery->getBattery();
    RobotPosition pose_ = pose->getPose();
    std::vector <float> lasers_ = lasers->getLasers();
    std::vector <Point32> sonar_ = sonar->getSonar();

    ss << "{\"battery\": {\"voltage\": ";
    ss << battery_;
    ss << "} ";
    
    ss << ", \"pose\": {\"position\": {\"x\":";
    ss << pose_.pos.x;
    ss << ", \"y\": ";
    ss << pose_.pos.y;
    ss << ", \"z\": ";
    ss << pose_.pos.z;
    ss << "}, \"orientation\": ";
    ss << pose_.ori;
    ss << "}, ";
    
    ss << "\"sonar\": {\"position\": [";   
    for (int i = 0; i < sonar_.size() - 1; i++){
        ss << "{\"x\": ";
        ss << sonar_[i].x;
        ss << ", \"y\": ";
        ss << sonar_[i].y;
        ss << ", \"z\": ";
        ss << sonar_[i].z;
        ss << ", \"distance\": ";
        ss << sonar_[i].distance;
        ss << "}, ";
    }
    ss << "{\"x\": ";
    ss << sonar_[sonar_.size()-1].x;
    ss << ", \"y\": ";
    ss << sonar_[sonar_.size()-1].y;
    ss << ", \"z\": ";
    ss << sonar_[sonar_.size()-1].z;
    ss << ", \"distance\": ";
    ss << sonar_[sonar_.size()-1].distance;
    ss << "}]} ";
        
    /*info_ += "lasers_: {scans: [";
    for (int i = 0; i < lasers_.size() - 1; i++){
        info_ += lasers_[i];
        info_ += ", ";
    }
    info_ += lasers_[lasers_.size()-1];
    info_ += "]}"; */
    ss << "}";
    info_ = ss.str();
    std::cout << info_ << std::endl;
    return info_;
}


#endif
