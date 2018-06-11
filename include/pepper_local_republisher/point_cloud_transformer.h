#ifndef _POINT_CLOUD_TRANSFORMER_H
#define _POINT_CLOUD_TRANSFORMER_H

#include <ros/ros.h>
#include <pcl_ros/transforms.h>
#include <tf/transform_listener.h>

class PointCloudTransformer
{
    private:
        ros::NodeHandle nh_;
        tf::TransformListener tl_;

        ros::Subscriber point_cloud_subscriber_;
        ros::Publisher point_cloud_publisher_;

        std::string output_point_cloud_parent_frame_id_;

        void pointCloudCallback(const sensor_msgs::PointCloud2ConstPtr& point_cloud);

    public:
        PointCloudTransformer();
        ~PointCloudTransformer(){}
};


#endif