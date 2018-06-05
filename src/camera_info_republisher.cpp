#include "pepper_local_republisher/camera_info_republisher.h"

CameraInfoRepublisher::CameraInfoRepublisher() : nh_("~"), camera_info_received_(false)
{
    double publish_frequency;
    bool static_camera_info;
    std::string input_camera_info_topic_name;
    std::string output_camera_info_topic_name;

    nh_.param("publish_frequency", publish_frequency, (double) 10.0);
    nh_.param("static_camera_info", static_camera_info, true);
    nh_.param("input_camera_info_topic_name", input_camera_info_topic_name, std::string("/camera/camera_info"));
    nh_.param("output_camera_info_topic_name", output_camera_info_topic_name, std::string("/camera_info_republisher/camera/camera_info"));
    nh_.param("output_camera_info_frame_id_name", output_camera_info_frame_id_name_, std::string(""));

    if(output_camera_info_frame_id_name_.empty())
    {
        change_frame_id_ = false;
    }
    else
    {
        change_frame_id_ = true;
    }

    ros::Rate rate(publish_frequency);

    camera_info_subscriber_ = nh_.subscribe(input_camera_info_topic_name, 1, &CameraInfoRepublisher::setCameraInfo, this);

    ROS_INFO("Waiting for camera info.");
    while (!camera_info_received_  && ros::ok())
    {
        ROS_INFO("Still waiting for camera info.");
        ros::spinOnce();
        rate.sleep();
    }

    if(static_camera_info)
    {
        ROS_INFO("Static_camera_info was set to True so shutting down camera info subscriber.");
        camera_info_subscriber_.shutdown();
    }

    ROS_INFO("Starting camera info publisher.");

    camera_info_publisher_ = nh_.advertise<sensor_msgs::CameraInfo>(output_camera_info_topic_name, 1);

    while (ros::ok())
    {
        camera_info_.header.seq = camera_info_.header.seq + 1;
        camera_info_.header.stamp = ros::Time::now();
        
        camera_info_publisher_.publish(camera_info_);

        ros::spinOnce();

        rate.sleep();
    }
}

void CameraInfoRepublisher::setCameraInfo(const sensor_msgs::CameraInfoConstPtr& camera_info)
{
    camera_info_ = *camera_info;
    if(change_frame_id_)
    {
        camera_info_.header.frame_id = output_camera_info_frame_id_name_;
    }
    camera_info_received_ = true;
    ROS_INFO("Received camera info.");
}