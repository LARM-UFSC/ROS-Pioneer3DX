#ifndef MOTORS_H
#define MOTORS_H

#include <geometry_msgs/Twist.h>
#include <std_srvs/Empty.h>
#include <std_msgs/Bool.h>

class Motors
{
    public:
        Motors(int rate, ros::NodeHandle *nh_);
        void setVelocity(float ang, float lin);
        void setSclAng(float scl_a);
        void setSclLin(float scl_l);
        bool getMotorsState();
        void enableMotors();
        void disableMotors();
    private:
        ros::NodeHandle *nh;
        void callbackMotorsState(const std_msgs::Bool msg);
        ros::Rate *loop_rate;
        ros::Publisher twist_pub;
        ros::Subscriber motors_state_sub;
        geometry_msgs::Twist twist;
        float scl_ang;
        float scl_lin;
        bool motor_state;
};

Motors::Motors(int rate, ros::NodeHandle *nh_){
    this->nh = nh_;
    //start local rate - not necessary at all
    loop_rate = new ros::Rate(1);
    //Start node
    twist_pub = nh->advertise<geometry_msgs::Twist>("RosAria/cmd_vel", 1);
    motors_state_sub = nh->subscribe("RosAria/motors_state", 1, &Motors::callbackMotorsState, this);
    //Set scalable velocity variables
    scl_ang = 1.0;
    scl_lin = 1.0;
    motor_state = false;
}

void Motors::callbackMotorsState(const std_msgs::Bool msg){
    motor_state = msg.data;
    loop_rate->sleep();
}

bool Motors::getMotorsState(){
    return motor_state;
}

void Motors::setVelocity(float ang, float lin){
    //Build the twist
    twist.angular.z = ang * scl_ang;
    twist.linear.x = lin * scl_lin;
    //Publish vel to robot
    twist_pub.publish(twist);
}

void Motors::setSclAng(float scl_a){
    //set scalable angular velocity factor
    scl_ang = scl_a;
}

void Motors::setSclLin(float scl_l){
    //set scalable linear velocity factor
    scl_lin = scl_l;
}

void Motors::enableMotors(){
    std::system("rosservice call /RosAria/enable_motors");
}

void Motors::disableMotors(){
    std::system("rosservice call /RosAria/disable_motors");
}

#endif
