#ifndef SONAR_H
#define SONAR_H

#include <sensor_msgs/PointCloud.h>

#define PRINT_SONAR 0

class Sonar
{
    public:
        Sonar(int rate, ros::NodeHandle *nh);
        std::vector < Point32 > getSonar();
    private:
        void callbackSonar(const sensor_msgs::PointCloud msg);
        ros::Rate *loop_rate;
        ros::Subscriber sensors_sub;
        std::vector < Point32 > medicoes;
};

Sonar::Sonar(int rate, ros::NodeHandle *nh){
    loop_rate = new ros::Rate(rate);

    sensors_sub = nh->subscribe("RosAria/sonar", 1, &Sonar::callbackSonar, this);
    medicoes.resize(8);
}

void Sonar::callbackSonar(const sensor_msgs::PointCloud msg){
#if PRINT_SONAR
    std::cout << "SONAR: "<< std::endl;
#endif
    for (int i = 0; i < 8; i++){
        medicoes[i].x = msg.points[i].x;
        medicoes[i].y = msg.points[i].y;
        medicoes[i].z = msg.points[i].z;
        medicoes[i].distance = sqrtf((medicoes[i].x * medicoes[i].x) + (medicoes[i].y * medicoes[i].y));
   	} 
#if PRINT_SONAR
    std::cout << "seq: " << msg.header.seq << ", frame_id: "  << msg.header.frame_id;
#endif  
#if PRINT_SONAR
    std::cout << std::endl;
#endif
	//loop_rate->sleep();
}

//Pega as medições do sensor
std::vector < Point32 >  Sonar::getSonar(){
    return medicoes;
}   

#endif
