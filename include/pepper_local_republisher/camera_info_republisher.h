#ifndef _CAMERA_INFO_REPUBLISHER_H
#define _CAMERA_INFO_REPUBLISHER_H

#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>

class CameraInfoRepublisher
{
    private:
        ros::NodeHandle nh_;
        sensor_msgs::CameraInfo camera_info_;
        std::string output_camera_info_frame_id_name_;
        bool change_frame_id_;
        bool camera_info_received_;

        ros::Subscriber camera_info_subscriber_;
        ros::Publisher camera_info_publisher_;

        void setCameraInfo(const sensor_msgs::CameraInfoConstPtr& camera_info);

    public:
        CameraInfoRepublisher();
        ~CameraInfoRepublisher(){}
};


#endif