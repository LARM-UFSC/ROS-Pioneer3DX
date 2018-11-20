#ifndef LASERS_H
#define LASERS_H

#include <sensor_msgs/LaserScan.h>
#include <vector>

#define PRINT_LASERS 1

class Lasers
{
    public:
        Lasers(int rate, ros::NodeHandle *nh);
        std::vector <float> getLasers();
    private:
        void callbackLasers(const sensor_msgs::LaserScan msg);
        ros::Rate *loop_rate;
        ros::Subscriber lasers_sub;
        std::vector <float> lasers_range;
};

Lasers::Lasers(int rate, ros::NodeHandle *nh){
    loop_rate = new ros::Rate(rate);
    lasers_sub = nh->subscribe("RosAria/lms2xx_1_laserscan", 1, &Lasers::callbackLasers, this);
}

std::vector <float> Lasers::getLasers(){
    return lasers_range;
}

void Lasers::callbackLasers(const sensor_msgs::LaserScan msg){
    lasers_range.clear();
    int meio = msg.ranges.size() / 2;
    int le = meio / 2 + meio / 4;
    int ld = msg.ranges.size() - le;
    lasers_range.push_back(msg.ranges[le]);
    lasers_range.push_back(msg.ranges[meio]);
    lasers_range.push_back(msg.ranges[ld]);
#if PRINT_LASERS
    std::cout << std::endl << std::endl << "Laser: " << msg.ranges[le] << ", " << msg.ranges[meio] << ", " << msg.ranges[ld] << std::endl << std::endl;
#endif
    //loop_rate->sleep();
}   


#endif
