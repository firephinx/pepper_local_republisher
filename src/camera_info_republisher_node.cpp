#include <ros/ros.h>
#include "pepper_local_republisher/camera_info_republisher.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "camera_info_republisher_node", ros::init_options::AnonymousName);

  CameraInfoRepublisher camera_info_republisher;

  return 0;
}