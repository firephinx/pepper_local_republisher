#ifndef _LASER_SCAN_REPUBLISHER_H
#define _LASER_SCAN_REPUBLISHER_H

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

class LaserScanRepublisher
{
    private:
        ros::NodeHandle nh_;

        ros::Subscriber laser_scan_subscriber_;
        ros::Publisher laser_scan_publisher_;
        std::string output_laser_scan_frame_id_name_;
        bool change_frame_id_;

        void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& laser_scan);

    public:
        LaserScanRepublisher();
        ~LaserScanRepublisher(){}
};


#endif