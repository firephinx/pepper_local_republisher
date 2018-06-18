#include "pepper_local_republisher/pose_republisher.h"

PoseRepublisher::PoseRepublisher() : nh_("~"), header_seq_(0)
{
    double publish_frequency;
    std::string input_pose_topic_name;
    std::string output_pose_topic_name;
    
    nh_.param("publish_frequency", publish_frequency, (double) 10.0);
    nh_.param("input_pose_topic_name", input_pose_topic_name, std::string("/amcl_pose"));
    nh_.param("output_pose_topic_name", output_pose_topic_name, std::string("/pepper_local_republisher/amcl_pose"));
    
    pose_subscriber_ = nh_.subscribe(input_pose_topic_name, 1, &PoseRepublisher::savePose, this);
    pose_publisher_ = nh_.advertise<geometry_msgs::PoseWithCovarianceStamped>(output_pose_topic_name, 1);

    ros::Rate rate(publish_frequency);
    pose_received_ = false;

    ROS_INFO("Waiting for initial pose.");

    while(!pose_received_)
    {
        ROS_INFO("Still waiting for initial pose.");
        ros::spinOnce();
        rate.sleep();
    }

    ROS_INFO("Received initial pose.");

    while(nh_.ok())
    {
        saved_pose_.header.seq = header_seq_;
        saved_pose_.header.stamp = ros::Time::now();
        pose_publisher_.publish(saved_pose_);
        header_seq_++;
    
        rate.sleep();
    }
}

void PoseRepublisher::savePose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose_ptr)
{
    saved_pose_ = *pose_ptr;
    pose_received_ = true;
}