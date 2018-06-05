#include "pepper_local_republisher/laser_scan_republisher.h"

LaserScanRepublisher::LaserScanRepublisher() : nh_("~")
{
	std::string laser_scan_input_topic_name;
    std::string laser_scan_output_topic_name;

    nh_.param("input_laser_scan_topic_name", laser_scan_input_topic_name, std::string("/scan"));
    nh_.param("output_laser_scan_topic_name", laser_scan_output_topic_name, std::string("/laser_scan_republisher/scan"));

    laser_scan_publisher_ = nh_.advertise<sensor_msgs::LaserScan>(laser_scan_output_topic_name, 1);
    laser_scan_subscriber_ = nh_.subscribe(laser_scan_input_topic_name, 1, &LaserScanRepublisher::laserScanCallback, this);
}

void LaserScanRepublisher::laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& laser_scan)
{
    laser_scan_publisher_.publish(*laser_scan);
}