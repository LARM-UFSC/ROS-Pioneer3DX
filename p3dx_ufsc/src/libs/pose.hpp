#ifndef POSE_H
#define POSE_H

#include <nav_msgs/Odometry.h>
#include "rostypes.hpp"

#define PRINT_POSE 0

class Pose
{
    public:
        Pose(ros::NodeHandle *nh);
        RobotPosition getPose();
    private:
        void callbackPose(const nav_msgs::Odometry msg);
        ros::Subscriber pose_sub;
        Point32 position;
        float orientation;
};

Pose::Pose(ros::NodeHandle *nh){
    //Start node
    pose_sub = nh->subscribe("RosAria/pose", 1, &Pose::callbackPose, this);
}

RobotPosition Pose::getPose(){
    RobotPosition newPos;
    newPos.pos = position;
    newPos.ori = orientation;
    return newPos;
}

void Pose::callbackPose(const nav_msgs::Odometry msg){
    position.x  = msg.pose.pose.position.x;
    position.y  = msg.pose.pose.position.y;
    position.z  = msg.pose.pose.position.z;
    orientation = msg.pose.pose.orientation.w;
#if PRINT_POSE
    std::cout << "x: " << position.x << ",y: " << position.y << ",z: " << position.z << std::endl; 
#endif
}

#endif
