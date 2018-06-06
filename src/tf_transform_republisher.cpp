#include "pepper_local_republisher/tf_transform_republisher.h"

TFTransformRepublisher::TFTransformRepublisher() : nh_("~")
{
    double publish_frequency;
    bool static_tf_transform;
    std::string input_tf_transform_parent_frame_id;
    std::string input_tf_transform_child_frame_id;
    std::string output_tf_transform_parent_frame_id;
    std::string output_tf_transform_child_frame_id;
    bool same_parent_frame;
    
    nh_.param("publish_frequency", publish_frequency, (double) 10.0);
    nh_.param("static_tf_transform", static_tf_transform, true);
    nh_.param("same_parent_frame", same_parent_frame, false);
    nh_.param("input_tf_transform_parent_frame_id", input_tf_transform_parent_frame_id, std::string("/camera_rgb_optical_frame"));
    nh_.param("input_tf_transform_child_frame_id", input_tf_transform_child_frame_id, std::string("/camera_depth_optical_frame"));
    nh_.param("output_tf_transform_parent_frame_id", output_tf_transform_parent_frame_id, std::string("/camera_rgb_optical_frame_republished"));
    nh_.param("output_tf_transform_child_frame_id", output_tf_transform_child_frame_id, std::string("/camera_depth_optical_frame_republished"));

    ros::Rate rate(publish_frequency);
    bool tf_transform_received = false;
    tf::StampedTransform transform;
    tf::Transform static_transform;
    tf::Transform identity_transform;

    ROS_INFO("Waiting for tf transform.");

    while(!tf_transform_received)
    {
        try 
        {
            tl_.waitForTransform(input_tf_transform_parent_frame_id, input_tf_transform_child_frame_id, ros::Time(0), ros::Duration(10.0));
            tl_.lookupTransform(input_tf_transform_parent_frame_id, input_tf_transform_child_frame_id, ros::Time(0), transform);
            static_transform.setOrigin(transform.getOrigin());
            static_transform.setRotation(transform.getRotation());
            tf_transform_received = true;
            ROS_INFO("Received tf transform.");
        }
        catch (tf::TransformException ex)
        {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
    }

    identity_transform.setOrigin( tf::Vector3(0.0, 0.0, 0.0) );
    tf::Quaternion q;
    q.setRPY(0, 0, 0);
    identity_transform.setRotation(q);

    while(nh_.ok())
    {
        if(!static_tf_transform)
        {
            try 
            {
                tl_.lookupTransform(input_tf_transform_parent_frame_id, input_tf_transform_child_frame_id, ros::Time(0), transform);
                static_transform.setOrigin(transform.getOrigin());
                static_transform.setRotation(transform.getRotation());
            }
            catch (tf::TransformException ex)
            {
                ROS_ERROR("%s",ex.what());
                ros::Duration(1.0).sleep();
            }
        }

        if(same_parent_frame)
        {
            tb_.sendTransform(tf::StampedTransform(static_transform, ros::Time::now(), input_tf_transform_parent_frame_id, output_tf_transform_child_frame_id));
        }
        else
        {
            tb_.sendTransform(tf::StampedTransform(identity_transform, ros::Time::now(), input_tf_transform_parent_frame_id, output_tf_transform_parent_frame_id));
            tb_.sendTransform(tf::StampedTransform(static_transform, ros::Time::now(), output_tf_transform_parent_frame_id, output_tf_transform_child_frame_id));
        }
    
        rate.sleep();
    }
}