#include <ros/ros.h>
#include "pepper_local_republisher/identity_tf_transform_publisher.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "identity_tf_transform_publisher_node", ros::init_options::AnonymousName);

  IdentityTFTransformPublisher identity_tf_transform_publisher;

  ros::spin();

  return 0;
}