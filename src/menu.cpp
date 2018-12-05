#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/TeleportAbsolute.h"
#include "turtlesim/SetPen.h"
#include <string>
#include <iostream>

#include <sensor_msgs/Joy.h>
#include <std_msgs/Int16.h>
#include "kobuki_msgs/BumperEvent.h"
#include "kobuki_msgs/CliffEvent.h"

using namespace std;
void menu();
void menuc1();
void menuc2();
void menuc3();
void badchoice();
void triangle();
void star();
void square();
void circle();
void run();
void run1();
void joy_callback(const sensor_msgs::Joy::ConstPtr& joyMsg);
void bumper_callback(const kobuki_msgs::BumperEvent::ConstPtr& bumpMsg);
void cliff_callback(const kobuki_msgs::CliffEvent::ConstPtr& cliffMsg);


ros::Publisher cmd_vel_pub;
ros::ServiceClient teleport_client;
ros::ServiceClient pen_client;
ros::Publisher cmd_vel_turtlebot;
ros::Subscriber joy_sub;  //Jsysoystick
ros::Subscriber bump_sub; //Bumper
ros::Subscriber cliff_sub; //Cliff
ros::Publisher music_pub; //Music
geometry_msgs::Twist msg;

float axes[6];
float buttons[4];
//bool inmenu = true;

void menu(){
    while(true){
    char choice;
    cout<<"You have entered the menu, please choose one of the following selections:"<<endl;
    cout<<"1. Drawing a shape using a keyboard"<<endl;
    cout<<"2. Free-draw using a joystic"<<endl;
    cout<<"3. Drawing a shape using joystic buttons (X, O, Triangle or Square)"<<endl;
    cout<<"0. Exit"<<endl;
    cin>>choice;

    if(choice=='1'){
        menuc1();
        }

    else if(choice=='2'){
        menuc2();
        }
    else if(choice=='3'){
        menuc3();
        }
    else if(choice=='0'){
        exit(0);
        }
    else{
        badchoice();
        menu();
        }
    }
}

void menuc1(){
    while(true){
    string input="";
    system("CLS");
    cout<<"Welcome! You have entered menu number 1!"<<endl;
    cout<<"Please enter a name of the shape you would like to print!"<<endl;
    cout<<"\nThe following options are:"<<endl;
    cout<<"SQUARE    TRIANGLE    STAR    CIRCLE"<<endl;
    cout<<""<<endl;
    cout<<"0. To come back to the menu"<<endl;
    string zero = "0";
    cin>>input;
    if(input==zero){
        menu();
        }
    else if(input=="triangle"){
      triangle();
    }
    else if(input=="star"){
      star();
    }
    else if(input=="circle"){
      circle();
    }
    else if(input=="square"){
      square();
    }
     else{
        badchoice();
        menuc1();
        }
    }
}

void menuc2(){
    system("CLS");
    cout<<"Welcome! You have entered menu number 2!"<<endl;
    cout<<"You are free to draw whatever you like!"<<endl;
    cout<<""<<endl;
    cout<<"0. Press X button to come back to main menu"<<endl;
    //inmenu = false;
    run();
  }

void menuc3(){
    system("CLS");
    cout<<"Welcome! You have enter menu number 3!"<<endl;
    cout<<"Press a button to draw a shape!"<<endl;
    cout<<""<<endl;
    cout<<"0. To come back to the menu"<<endl;
    run1();

}

void badchoice(){
    cout<<"You can not choose that!"<<endl;
    system("pause");
}

void triangle(){
    msg.linear.x = 1.0;
    cmd_vel_turtlebot.publish(msg);
    msg.linear.x = 3.0;
    cmd_vel_turtlebot.publish(msg);

    msg.linear.x = 0.0;
    msg.angular.z = 2.0;
    cmd_vel_turtlebot.publish(msg);

    msg.linear.x = 3.0;
    msg.angular.z = 0.0;
    cmd_vel_turtlebot.publish(msg);

    msg.linear.x = 0.0;
    msg.angular.z = 2.17;
    cmd_vel_turtlebot.publish(msg);

    msg.linear.x = 3.22;
    msg.angular.z = 0.0;
    cmd_vel_turtlebot.publish(msg);

}

void star(){

  msg.linear.x = 0.14;
  msg.angular.z = 5.5;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.520;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.3;
  msg.angular.z = 3;
  cmd_vel_turtlebot.publish(msg);
  msg.angular.z = 5.4;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.526;
  msg.angular.z = 5.55;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.55;
  msg.angular.z = 5.55;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.53;
  msg.angular.z = 5.65;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.54;
  msg.angular.z = 5.85;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.52;
  msg.angular.z = 5.72;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.5;
  msg.angular.z = 5.85;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.510;
  msg.angular.z = 5.65;
  cmd_vel_turtlebot.publish(msg);

  msg.linear.x = 0.495;
  msg.angular.z = 5.55;
  cmd_vel_turtlebot.publish(msg);

}
void square(){
  float box_size = ros::param::param("~box_size", 3.0);
  turtlesim::SetPen pen_srv;
  pen_srv.request.off = true;
  pen_client.call(pen_srv);
  turtlesim::TeleportAbsolute srv;

  srv.request.x = 5.5-box_size/2;
  srv.request.y = 5.5-box_size/2;
  teleport_client.call(srv);

  pen_srv.request.off = false;
  pen_srv.request.width = 10;
  pen_srv.request.r = 130;
  pen_srv.request.g = 130;
  pen_client.call(pen_srv);

  srv.request.x = 5.5-box_size/2;
  srv.request.y = 5.5+box_size/2;
  teleport_client.call(srv);

  srv.request.x = 5.5+box_size/2;
  srv.request.y = 5.5+box_size/2;
  teleport_client.call(srv);

  srv.request.x = 5.5+box_size/2;
  srv.request.y = 5.5-box_size/2;
  teleport_client.call(srv);

  srv.request.x = 5.5-box_size/2;
  srv.request.y = 5.5-box_size/2;
  teleport_client.call(srv);

  pen_srv.request.off = true;
  pen_client.call(pen_srv);

  srv.request.x = 5.5;
  srv.request.y = 5.5;
  teleport_client.call(srv);

  pen_srv.request.off = false;
  pen_srv.request.width = 4;
  pen_srv.request.r = 10;
  pen_srv.request.g = 130;
  pen_srv.request.b = 200;
  pen_client.call(pen_srv);
}
void circle(){
  msg.linear.x = 1*15;
  msg.angular.z = 0.5*15;
  cmd_vel_turtlebot.publish(msg);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "menu");
    ros::NodeHandle nh;
    cmd_vel_turtlebot = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    joy_sub = nh.subscribe<sensor_msgs::Joy>("/joy", 5, joy_callback); //changed from 1 to 5
    bump_sub = nh.subscribe("/mobile_base/events/bumper", 1, bumper_callback);
    cliff_sub = nh.subscribe("/mobile_base/events/cliff", 5, cliff_callback);
    music_pub = music_pub = nh.advertise<std_msgs::Int16>("/music", 2);
    menu();
    return 0;
}

void run(){
  ros::NodeHandle nh;

  ros::Duration(1.0).sleep();

  geometry_msgs::Twist velMsg;
  float linSpeed = 0.4;
  float angSpeed = 1;

  ros::Rate r(25);
  while(ros::ok())
  {
    nh.getParam("/mine_explorer/angSpeed", angSpeed);
    nh.getParam("/mine_explorer/linSpeed", linSpeed);
    //Set speed, linear and angular, publish
    velMsg.linear.x = axes[1]*linSpeed;
    //std::cout << "Axes[1]: " << axes[1] << ", linspeed: " << linSpeed << std::endl;
    velMsg.angular.z = axes[0]*angSpeed;
    cmd_vel_turtlebot.publish(velMsg);
    ros::spinOnce();
    r.sleep();
  }
}
void run1(){
  ros::NodeHandle nh;

  ros::Duration(1.0).sleep();

  ros::Rate r(25);
  while(ros::ok()) {
    ros::spinOnce();
    r.sleep();
  }

}
void bumper_callback(const kobuki_msgs::BumperEvent::ConstPtr& bumpMsg)
{

}

void cliff_callback(const kobuki_msgs::CliffEvent::ConstPtr& cliffMsg)
{

}

void joy_callback(const sensor_msgs::Joy::ConstPtr& joyMsg)
{
  for (size_t i = 0; i < sizeof(joyMsg->axes)/sizeof(joyMsg->axes[0]); i++) {
    axes[i] = joyMsg->axes[i];
  }
  if(joyMsg->buttons[0]) // Get back to the menu!
  {
    //inmenu = true;
    menu();
  }
  else if(joyMsg->buttons[1]){
    star();
  }
  else if(joyMsg->buttons[2]){
    triangle();
  }
  else if(joyMsg->buttons[3]){
    circle();
  }

  ///Four buttons for sound effects
  /*for (size_t i = 0; i < 4; i++)
  {
    if(joyMsg->buttons[i])
    {
      playMusic(i+1); //Music values from 1-4, as such, i+1 is used, as i is 0-3
      std::cout << "sound: " << i << " is playing!" << std::endl;
    }
  }*/
}
