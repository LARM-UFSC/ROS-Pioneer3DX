
#include <signal.h>
#include <iostream>
#include <inttypes.h>
#ifdef ADEPT_PKG
  #include <Aria.h>
#else
  #include <Aria/Aria.h>
#endif
#include <std_msgs/Char.h>
#include <std_msgs/String.h>
#include <string.h>
#include <string>
#include "ros/ros.h"
#include "monitor.hpp"

void quit(int sig)
{
    std::cout << "Finalizando programa!" << std::endl;
    ros::shutdown();
    exit(0);
}

class SocketServerInfo {
    public:
        SocketServerInfo(int, int);
        bool WaitConnection();
        void mainLoop();
    private: 
        void timerCallback(const ros::TimerEvent& event);
        // Ros components
        ros::NodeHandle Node;
        ros::Rate *loop_rate;
        ros::Publisher publish, publish_info;
        ros::Timer timer;
        Monitor *monitor;
        // Aria components
        ArSocket serverSock, sendSock;
};

SocketServerInfo::SocketServerInfo(int rate, int port = 7778){
    loop_rate = new ros::Rate(rate);
    Aria::init();
    publish_info = Node.advertise<std_msgs::String>("robotInfo", 1);
    monitor = new Monitor();
    timer = Node.createTimer(ros::Duration(1), &SocketServerInfo::timerCallback, this);

    //Open socket server
    if (serverSock.open(port, ArSocket::TCP)) {
        ArLog::log(ArLog::Normal, "Servidor de informações aberto na porta: %d.", port);
    } else {
        ArLog::log(ArLog::Normal, "Falha ao abrir servidor na porta: %s.", serverSock.getErrorStr().c_str());
        Aria::exit(-1);
        ros::shutdown();
    }

    signal(SIGINT,quit);
}

void SocketServerInfo::timerCallback(const ros::TimerEvent& event){
    std::string info_ = monitor->getInfo();

    std_msgs::String msg;
    msg.data = info_;

    publish_info.publish(msg);

    char *buffer = new char[msg.data.size()];
    for (int i = 0; i < msg.data.size(); i++)
        buffer[i] = msg.data[i];

    sendSock.write(buffer, msg.data.size());

    ros::spinOnce();
}


bool SocketServerInfo::WaitConnection(){
    if (serverSock.accept(&sendSock)) {
        
        ArLog::log(ArLog::Normal, "Cliente conectado.");
        std::cout << sendSock.getIPString() << std::endl;

        return true;
    } else {
        ArLog::log(ArLog::Terse, "Erro ao conectar: %s.", serverSock.getErrorStr().c_str());
        return false;
    }
}

void SocketServerInfo::mainLoop(){
    uint8_t buff[128];
    size_t strSize;
    while(true){
        
        ros::spinOnce();
    }
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "socket_info");

    SocketServerInfo server(1000, 7778);

    while(!server.WaitConnection());

    server.mainLoop();

    ros::spin();

    ros::shutdown();

    return 0;
}