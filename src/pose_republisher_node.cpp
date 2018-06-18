#include <ros/ros.h>
#include "pepper_local_republisher/pose_republisher.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pose_republisher_node", ros::init_options::AnonymousName);

  PoseRepublisher pose_republisher;

  ros::spin();

  return 0;
}