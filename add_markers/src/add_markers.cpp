#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Pose.h>
#include <string>

using namespace std;

ros::Publisher marker_publisher;


void handleMarker(string name, int id, float p_x, float p_y,float p_orientation, bool status)
{
   // Set our initial shape type to be a sphere
  uint32_t shape = visualization_msgs::Marker::SPHERE;


  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = name;
  marker.id = id;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  if(status) {
    marker.action = visualization_msgs::Marker::ADD;
  } else {
    marker.action = visualization_msgs::Marker::DELETE;
  }

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = p_x;
  marker.pose.position.y = p_y;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = p_orientation;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.3;
  marker.scale.y = 0.3;
  marker.scale.z = 0.3;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();
  // Publish the marker
 // while (marker_publisher.getNumSubscribers() < 1)
   //    {
     //    if (!ros::ok())
       //  {
       //   return 0;
        // }
      //   ROS_WARN_ONCE("Please create a subscriber to the marker");
      //   sleep(1);
      // }

  marker_publisher.publish(marker);
}


int main( int argc, char** argv )
{
  float pick_x = 4.5;
  float pick_y = 3;
  float pick_orientation = 1.41;

  float drop_x = -2.0;
  float drop_y= -0.1;
  float drop_orientation = 1.3;

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;

  ros::Rate r(1);
  marker_publisher = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Publish the marker
  while (marker_publisher.getNumSubscribers() < 1)
  {
    if (!ros::ok())
    {
      return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }

 // Creation of first marker
  ROS_INFO("Pick-up marker created");
  handleMarker("Pick-up-marker" , 1, pick_x, pick_y, pick_orientation, true);

  // 5 sec delay
  ROS_INFO("Wait for 5 sec");
  sleep(5.0);

 // Deletion of first marker
  handleMarker("Pick-up-marker" , 1, pick_x, pick_y, pick_orientation, false);

  ROS_INFO("Wait for 5 sec");
  sleep(5.0);
 // Creation of second marker
  ROS_INFO("Drop-off marker created");
  handleMarker("Drop-off-marker" , 2, drop_x, drop_y, drop_orientation, true);

  ROS_INFO("Waiting for 5 seconds to delete marker");
  sleep(5.0);
 //Deletion of second marker
  handleMarker("Drop-off-marker" , 2, drop_x, drop_y, drop_orientation, false);
  sleep(5.0);

  r.sleep();
}
