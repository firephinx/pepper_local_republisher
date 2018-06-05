#include "pepper_local_republisher/laser_scan_republisher.h"

LaserScanRepublisher::LaserScanRepublisher() : nh_("~")
{
    std::string input_laser_scan_topic_name;
    std::string output_laser_scan_topic_name;

    nh_.param("input_laser_scan_topic_name", input_laser_scan_topic_name, std::string("/scan"));
    nh_.param("output_laser_scan_topic_name", output_laser_scan_topic_name, std::string("/laser_scan_republisher/scan"));
    nh_.param("output_laser_scan_frame_id_name", output_laser_scan_frame_id_name_, std::string(""));

    if(output_laser_scan_frame_id_name_.empty())
    {
        change_frame_id_ = false;
    }
    else
    {
        change_frame_id_ = true;
    }

    laser_scan_publisher_ = nh_.advertise<sensor_msgs::LaserScan>(output_laser_scan_topic_name, 1);
    laser_scan_subscriber_ = nh_.subscribe(input_laser_scan_topic_name, 1, &LaserScanRepublisher::laserScanCallback, this);
}

void LaserScanRepublisher::laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& laser_scan_msg_const_ptr)
{
    if(change_frame_id_)
    {
        sensor_msgs::LaserScan laser_scan_msg;
        laser_scan_msg.header.seq = laser_scan_msg_const_ptr->header.seq;
        laser_scan_msg.header.stamp = laser_scan_msg_const_ptr->header.stamp;

        // Change the frame_id of the laser scan message to the new frame_id
        laser_scan_msg.header.frame_id = output_laser_scan_frame_id_name_;

        laser_scan_msg.angle_min = laser_scan_msg_const_ptr->angle_min;
        laser_scan_msg.angle_max = laser_scan_msg_const_ptr->angle_max;
        laser_scan_msg.angle_increment = laser_scan_msg_const_ptr->angle_increment;
        laser_scan_msg.time_increment = laser_scan_msg_const_ptr->time_increment;
        laser_scan_msg.scan_time = laser_scan_msg_const_ptr->scan_time;
        laser_scan_msg.range_min = laser_scan_msg_const_ptr->range_min;
        laser_scan_msg.range_max = laser_scan_msg_const_ptr->range_max;
        laser_scan_msg.ranges = laser_scan_msg_const_ptr->ranges;
        laser_scan_msg.intensities = laser_scan_msg_const_ptr->intensities;

        laser_scan_publisher_.publish(laser_scan_msg);
    }
    else
    {
        // Publish original laser scan message
        laser_scan_publisher_.publish(*laser_scan_msg_const_ptr);
    }
}