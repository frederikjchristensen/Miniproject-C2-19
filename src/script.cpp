#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <sensor_msgs/Joy.h>
#include <iostream>

void joy_callback(const sensor_msgs::Joy::ConstPtr& joyMsg);


float axes[6];

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "script");

  //Defining subs and pubs ==============================================
  ros::NodeHandle nh;
  ros::Publisher script_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 10);
  ros::Subscriber joy_sub = nh.subscribe<sensor_msgs::Joy>("/joy", 1, joy_callback);

  ros::spin();

  return 0;
}

//Defining functions ====================================================

void joy_callback(const sensor_msgs::Joy::ConstPtr& joyMsg)
{
  //Retrieve Axes:
  for (size_t i = 0; i < sizeof(joyMsg->axes)/sizeof(joyMsg->axes[0]); i++) {
    axes[i] = joyMsg->axes[i];
  }

  //Four buttons for sound effects
  for (size_t i = 0; i < 4; i++)
  {
    if(joyMsg->buttons[i])
    {

    }
  }
}
