#ifndef _POSE_REPUBLISHER_H
#define _POSE_REPUBLISHER_H

#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

class PoseRepublisher
{
    private:
        ros::NodeHandle nh_;

        ros::Subscriber pose_subscriber_;
        ros::Publisher pose_publisher_;

        bool pose_received_;
        geometry_msgs::PoseWithCovarianceStamped saved_pose_;

        void savePose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose);

    public:
        PoseRepublisher();
        ~PoseRepublisher(){}
};


#endif