
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

void quit(int sig)
{
    std::cout << "Finalizando programa!" << std::endl;
    ros::shutdown();
    exit(0);
}

class SocketServer {
    public:
        SocketServer(int, int);
        bool WaitConnection();
        void mainLoop();
    private: 
        // Ros components
        ros::NodeHandle Node;
        ros::Rate *loop_rate;
        ros::Publisher publish;
        // Aria components
        ArSocket serverSock, receiveSock;
};

SocketServer::SocketServer(int rate, int port = 7777){
    loop_rate = new ros::Rate(rate);
    Aria::init();
    publish = Node.advertise<std_msgs::Char>("socketCom", 1);

    //Open socket server
    if (serverSock.open(port, ArSocket::TCP)) {
        ArLog::log(ArLog::Normal, "Servidor aberto na porta: %d.", port);
    } else {
        ArLog::log(ArLog::Normal, "Falha ao abrir servidor na porta: %s.", serverSock.getErrorStr().c_str());
        Aria::exit(-1);
        ros::shutdown();
    }

    signal(SIGINT,quit);
}

bool SocketServer::WaitConnection(){
    if (serverSock.accept(&receiveSock)) {
        
        ArLog::log(ArLog::Normal, "Cliente conectado.");
        std::cout << receiveSock.getIPString() << std::endl;

        return true;
    } else {
        ArLog::log(ArLog::Terse, "Erro ao conectar: %s.", serverSock.getErrorStr().c_str());
        return false;
    }
}

void SocketServer::mainLoop(){
    uint8_t buff[128];
    size_t strSize;
    while(true){
        strSize = receiveSock.read(buff, sizeof(buff));

        if (strSize > 0)
        {
            char *buffer = new char[strSize];
            for (int i = 0; i < strSize; i++){
                buffer[i] = (char) buff[i];
            }

            #if DEBUG
            //sucesso
            buffer[strSize]='\0';
            ArLog::log(ArLog::Normal, "Msg: \"%s\"", buffer);
            #endif

            std_msgs::Char msg;
            msg.data = buffer[0];
            
            publish.publish(msg);
            delete buffer;
        }
        else
        {
            ArLog::log(ArLog::Terse, "Error!");
            receiveSock.close();
            while(!WaitConnection());
        }

        ros::spinOnce();
    }
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "socket");

    SocketServer server(1000, 7777);

    while(!server.WaitConnection());

    server.mainLoop();

    ros::spin();

    ros::shutdown();

    return 0;
}