#include <iostream>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Path.h>
#include "sample_waypoints.h"
#include <vector>
#include <deque>
#include <boost/format.hpp>
#include <eigen3/Eigen/Dense>

using namespace std;
geometry_msgs::PointStamped pos;
geometry_msgs::PoseStamped goal;
geometry_msgs::Vector3 p0;
geometry_msgs::Vector3 p1;
geometry_msgs::Vector3 p2;
geometry_msgs::Vector3 p3;
geometry_msgs::Vector3 p4;
geometry_msgs::Vector3 p5;
geometry_msgs::Vector3 p6;
geometry_msgs::Vector3 p7;
geometry_msgs::Vector3 p8;
geometry_msgs::Vector3 p_desired;




std::vector<geometry_msgs::Vector3> path;




ros::Publisher pub1;

bool has_pos = false;
void pos_Callback(const geometry_msgs::PointStamped::ConstPtr& msg)
{
   pos = *msg;
   has_pos = true;
 

}


int main(int argc, char** argv) {
    ros::init(argc, argv, "goal_pub");
    ros::NodeHandle n1("~");
    ros::Subscriber sub1 = n1.subscribe("/firefly/ground_truth/position", 1, pos_Callback);
    pub1 = n1.advertise<geometry_msgs::PoseStamped>("/goal_pub/goal1", 1);
   
    int i = 0;
    p0.x =  0; 
    p0.y =  0;
    p0.z =  2;
    p1.x =  -6.56; 
    p1.y =  -13.85;
    p1.z =  6.22;
    p2.x =  -13.30; 
    p2.y =  -28.67;
    p2.z =  13.76;
    p3.x =  14.37; 
    p3.y =  -26.57;
    p3.z =  11.00;
    p4.x =  13.76; 
    p4.y =  -26.57;
    p4.z =  11.00;
    p5.x =  29.19; 
    p5.y =  5.13;
    p5.z =  9.62;
    p6.x =  14.35; 
    p6.y =  -8.72;
    p6.z =  7.20;
    p7.x = -4.06; 
    p7.y =  -5.97;
    p7.z =  9.02;
    p8.x =  0; 
    p8.y =  0;
    p8.z =  2;
    p_desired = p0;
    path.push_back(p0);
    path.push_back(p1);
   path.push_back(p2);
   path.push_back(p3);
   path.push_back(p4);
   path.push_back(p5);
   path.push_back(p6);
   path.push_back(p7);
   path.push_back(p8);
   ros::Rate loop_rate(50);
    while(ros::ok())
{
   if(has_pos)
   {
    if(fabs(pos.point.x-p_desired.x)<0.3 && fabs(pos.point.y-p_desired.y)<0.3 && fabs(pos.point.z-p_desired.z)<0.3 && i<path.size())
     {
         i++;
         p_desired  = path[i];
         goal.header.stamp  = ros::Time::now();
         goal.pose.position.x = p_desired.x;
         goal.pose.position.y = p_desired.y;
         goal.pose.position.z = p_desired.z;
         goal.header.stamp  = ros::Time::now(); 
         goal.header.frame_id = "world";
         pub1.publish(goal);
         ROS_INFO("NEXT");
     }
         
     
     

   } 
   ros::spinOnce();
   loop_rate.sleep();

}

  

    
    return 0;
}
