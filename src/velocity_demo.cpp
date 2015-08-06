#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/Joy.h>
#include <nav_msgs/Path.h>
// #include <mavros/utils.h>
#include <math.h>

/*
First get the set-point location. 
Get GPS local position (   through TF format ???? ). 
If local pose in range of set point, 
      Get new set point, and then repeat. 
*/

int ctr=0; 
double sp[4][3];

class setpoint
{ 
  public: 
    
    setpoint();
    //Defining variables. 
    geometry_msgs::PoseStamped gps_local_own_pose;
    geometry_msgs::TwistStamped vel_set_point; 

    //Setting up the node handler. 
    ros::NodeHandle nh_;
    //Setting a publisher for publishing the outgoing set_points to the Pixhawk.
    ros::Publisher vel_set_point_pub, vel_set_point_pub_2;
    //Setting a subscriber to take in the local position of the pixhawk (from GPS). 
    ros::Subscriber gps_local_own_pose_sub;


    void update_set_point()
      {          
          vel_set_point.header.frame_id = "base_footprint";
          vel_set_point.header.stamp = ros::Time::now();

          //Setting velocity values. 
          vel_set_point.twist.linear.x = 2; 
          vel_set_point.twist.linear.y = 0; 
          vel_set_point.twist.linear.z = 0; 

          vel_set_point_pub.publish(vel_set_point);
          vel_set_point_pub_2.publish(vel_set_point);
      }
    //Now writing corresponding callback function. 
    void gps_local_own_pose_callback(const geometry_msgs::PoseStamped::ConstPtr& local_pose_gps)
      {   
          // double epsilon = 0.5;
          gps_local_own_pose = *local_pose_gps;

          std::cerr<<"The gps local own pose:"<<gps_local_own_pose.pose.position.x<<"  "<<gps_local_own_pose.pose.position.y<<"  "<<gps_local_own_pose.pose.position.z<<std::endl;                   
          update_set_point();
      }

    
};

setpoint::setpoint()
   {   
      //Advertising the setpoint data. 
      vel_set_point_pub = nh_.advertise<geometry_msgs::Twist> ("/mavros/setpoint/cmd_vel",1);
      vel_set_point_pub_2 = nh_.advertise<geometry_msgs::Twist> ("/mavros/setpoint_velocity/cmd_vel",1);

      gps_local_own_pose_sub = nh_.subscribe("mavros/position/local",1,&setpoint::gps_local_own_pose_callback,this);
   }

int main(int argc, char** argv)
{
  //Initialize the node. 
  ros::init(argc, argv, "pub_mav_follow");
  
  //Create an object of class setpoint. 
  setpoint setpoint_ob;

  ros::spin();
}

