#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

double height = 0.75;

double width = 1.0;
double depth = 1.5;
double offset = 0.5;

double legradius = 0.05;
double colorr = 0.957;
double colorg = 0.482;
double colorb = 0.063;
double colora = 0.66;



visualization_msgs::Marker create_leg(int ln)
{
  visualization_msgs::Marker marker;
  marker.header.frame_id = "/base_link";
  marker.header.stamp = ros::Time::now();
  marker.ns = "table_markers";
  marker.id = ln;
  marker.type = visualization_msgs::Marker::CYLINDER;
  marker.action = visualization_msgs::Marker::ADD;

  switch(ln)
  {
    case 0:
      marker.pose.position.x = offset + depth - legradius/2;
      marker.pose.position.y = -width/2 + legradius/2;
      break;
    case 1:
      marker.pose.position.x = offset + depth - legradius/2;
      marker.pose.position.y = width/2 - legradius/2;
      break;
    case 2:
      marker.pose.position.x = offset + legradius/2;
      marker.pose.position.y = -width/2 + legradius/2;
      break;
    case 3:
      marker.pose.position.x = offset + legradius/2;
      marker.pose.position.y = width/2 - legradius/2;
      break;
  }

  marker.pose.position.z = height/2;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  marker.scale.x = legradius;
  marker.scale.y = legradius;
  marker.scale.z = height;

  marker.color.r = colorr;
  marker.color.g = colorg;
  marker.color.b = colorb;
  marker.color.a = colora;

  marker.lifetime = ros::Duration();

  return marker;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "create_table");
  ros::NodeHandle n;
  ros::Rate r(10);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("create_table_marker", 1);

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    marker.header.frame_id = "/base_link";
    marker.header.stamp = ros::Time::now();
    marker.ns = "table_markers";
    marker.id = 10;
    marker.type = visualization_msgs::Marker::CUBE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = offset+depth/2;
    marker.pose.position.y = 0;
    marker.pose.position.z = height;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = depth;
    marker.scale.y = width;
    marker.scale.z = 0.025;

  marker.color.r = colorr;
  marker.color.g = colorg;
  marker.color.b = colorb;
  marker.color.a = colora;

    marker.lifetime = ros::Duration();

    // Publish the marker
    marker_pub.publish(marker);

    for(int i = 0; i < 4; i++)
    {
      marker_pub.publish(create_leg(i));
    }
  }
}
