#include "pepper_local_republisher/identity_tf_transform_publisher.h"

IdentityTFTransformPublisher::IdentityTFTransformPublisher() : nh_("~")
{
    double publish_frequency;
    std::string tf_transform_parent_frame_id;
    std::string tf_transform_child_frame_id;
    
    nh_.param("publish_frequency", publish_frequency, (double) 10.0);
    nh_.param("tf_transform_parent_frame_id", tf_transform_parent_frame_id, std::string("/base_footprint"));
    nh_.param("tf_transform_child_frame_id", tf_transform_child_frame_id, std::string("/pepper_local_republisher/base_footprint"));

    ros::Rate rate(publish_frequency);
    tf::Transform identity_transform;

    identity_transform.setOrigin( tf::Vector3(0.0, 0.0, 0.0) );
    tf::Quaternion q;
    q.setRPY(0, 0, 0);
    identity_transform.setRotation(q);

    while(nh_.ok())
    {
        tb_.sendTransform(tf::StampedTransform(identity_transform, ros::Time::now(), tf_transform_parent_frame_id, tf_transform_child_frame_id));
    
        rate.sleep();
    }
}