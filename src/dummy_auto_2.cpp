#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
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

class setpoint
{ 
  public: 
    
    setpoint();
    //Defining variables. 
    geometry_msgs::PoseStamped set_point_pose, gps_local_own_pose, gps_local_master_pose;
    bool reached_set_pt;

    
  // private: 
    //Setting up the node handler. 
    ros::NodeHandle nh_;
    //Setting a publisher for publishing the outgoing set_points to the Pixhawk.
    ros::Publisher set_point_pub, set_point_pub_1, set_point_pub_2, set_point_pub_3, set_point_pub_4, set_point_pub_5; 
    //Setting a subscriber to take in the local position of the pixhawk (from GPS). 
    ros::Subscriber gps_local_own_pose_sub;

    ros::Subscriber gps_local_master_pose_sub;

    //Now writing corresponding callback function. 
   
    void gps_local_own_pose_callback(const geometry_msgs::PoseStamped::ConstPtr& local_pose_gps)
      {   double epsilon = 0.5;
          gps_local_own_pose = *local_pose_gps;

          // if ((fabs(gps_local_own_pose.pose.position.x - set_point_pose.pose.position.x)<epsilon)
          //   &&(fabs(gps_local_own_pose.pose.position.y - set_point_pose.pose.position.y)<epsilon)
          //   &&(fabs(gps_local_own_pose.pose.position.z - set_point_pose.pose.position.z)<epsilon))
          //     {  reached_set_pt = true; 
          //     }

          // if ((fabs(gps_local_own_pose.x - set_point_pose.x)<epsilon)&&(fabs(gps_local_own_pose.y - set_point_pose.y)<epsilon)&&(fabs(gps_local_own_pose.z - set_point_pose.z)<epsilon))
          //     {  reached_set_pt = true; 
          //     }

          std::cerr<<"The gps local own pose:"<<gps_local_own_pose.pose.position.x<<"  "<<gps_local_own_pose.pose.position.y<<"  "<<gps_local_own_pose.pose.position.z<<std::endl;

	  set_point_pose.header.frame_id = "base_footprint";
	  set_point_pose.header.stamp = ros::Time::now();
          set_point_pose.pose.position.x = gps_local_own_pose.pose.position.x+10;
          set_point_pose.pose.position.y = gps_local_own_pose.pose.position.y;
          set_point_pose.pose.position.z = gps_local_own_pose.pose.position.z+5;
		

	 set_point_pose.pose.position.x = -5;
	 set_point_pose.pose.position.y = -30;
	 set_point_pose.pose.position.z = 15;
	  
  	  set_point_pose.pose.orientation.w = 1;
          set_point_pub.publish(set_point_pose);
          set_point_pub_1.publish(set_point_pose);
          set_point_pub_2.publish(set_point_pose);
          set_point_pub_3.publish(set_point_pose);
          set_point_pub_4.publish(set_point_pose);
	  set_point_pub_5.publish(set_point_pose);
          
      }

    void gps_local_master_pose_callback(const geometry_msgs::PoseStamped::ConstPtr& local_master_pose_gps)
      {   gps_local_master_pose = *local_master_pose_gps;
          std::cerr<<"The gps local master pose:"<<gps_local_master_pose.pose.position.x<<"  "<<gps_local_master_pose.pose.position.y<<"  "<<gps_local_master_pose.pose.position.z<<std::endl;
         
          update_set_point();
          std::cerr<<"The set point pose:"<<set_point_pose.pose.position.x<<"  "<<set_point_pose.pose.position.y<<"  "<<set_point_pose.pose.position.z<<std::endl;
      }

    // void update_set_point(double x, double y, double z)
    void update_set_point()
      {          
          // set_point_pose.pose.position.x = gps_local_master_pose.pose.position.x - gps_local_own_pose.pose.position.x + 10;
          // set_point_pose.pose.position.y = gps_local_master_pose.pose.position.y - gps_local_own_pose.pose.position.y;
          // set_point_pose.pose.position.z = gps_local_master_pose.pose.position.z - gps_local_own_pose.pose.position.z;

          set_point_pose.pose.position.x = gps_local_master_pose.pose.position.x+10;
          set_point_pose.pose.position.y = gps_local_master_pose.pose.position.y;
          set_point_pose.pose.position.z = gps_local_master_pose.pose.position.z;


          // set_point_pose.pose.orientation.w = 0;
          set_point_pub.publish(set_point_pose);
          set_point_pub_1.publish(set_point_pose);
          set_point_pub_2.publish(set_point_pose);
          set_point_pub_3.publish(set_point_pose);
          set_point_pub_4.publish(set_point_pose);
	  set_point_pub_5.publish(set_point_pose);
          // ros::Rate r(100);
          // while (reached_set_pt==false)
          //     { r.sleep();
          //     }
          // mav_path_pub = nh_.advertise<geometry_msgs::PoseStamped>("set_point",1);
      }
};

setpoint::setpoint()
   {   
      //Advertising the setpoint data. 
      // set_point_pub = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint/local_position",1);
      // set_point_pub = nh_.advertise<geometry_msgs::PoseStamped>("/dummy_mavros/setpoint/local_position",1);
      // set_point_pub = nh_.advertise<geometry_msgs::PoseStamped>("/odroid_2/mavros/setpoint_position/local_position",1);
      set_point_pub = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local_position",1);
      set_point_pub_1 = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint/local_position",1);
      set_point_pub_2 = nh_.advertise<geometry_msgs::PoseStamped>("/local_position",1);
      set_point_pub_3 = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local",1);
      set_point_pub_4 = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint/local",1);
      set_point_pub_5 = nh_.advertise<geometry_msgs::PoseStamped>("/local",1);

//   set_point_pub_1 = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint/local_position",1);

      //Subscribing to gps local pose. 
      // gps_local_own_pose_sub = nh_.subscribe("mavros/local_position/local",1,&setpoint::gps_local_own_pose_callback,this);
//      gps_local_own_pose_sub = nh_.subscribe("odroid_2/mavros/position/local",1,&setpoint::gps_local_own_pose_callback,this);
      gps_local_own_pose_sub = nh_.subscribe("mavros/position/local",1,&setpoint::gps_local_own_pose_callback,this);


      // gps_local_master_pose_sub = nh_.subscribe("odroid_2/mavros/position/local",1,&setpoint::gps_local_master_pose_callback,this);
      // gps_local_own_pose_sub = nh_.subscribe<geometry_msgs::PoseStamped>("local_position/local",gps_local_own_pose_callback,this);

      //If the GPS goal and GPS local pose are close to each other, update set point. 
      // setpoint::update_set_point();

  }

int main(int argc, char** argv)
{
  //Initialize the node. 
  ros::init(argc, argv, "pub_mav_follow");
  

  //Create an object of class setpoint. 
  setpoint setpoint_ob;

  // int i =0;
  // while(nh_.ok())
  //   {   
  //       setpoint_ob.update_set_point(0,0,0);
  //       i++;

  //       r.sleep();
  //   }

  ros::spin();
}

