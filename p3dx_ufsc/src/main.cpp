#include <ros/ros.h>
#include <signal.h>
#include <iostream>
#include "AutoRun.hpp"



int main(int argc, char** argv)
{
    ros::init(argc, argv, "main");
    AutoRun autorun;
    autorun.mainLoop();

    ros::spin();
    return 0;
}























