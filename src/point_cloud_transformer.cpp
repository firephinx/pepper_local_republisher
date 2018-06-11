#include "pepper_local_republisher/point_cloud_transformer.h"

PointCloudTransformer::PointCloudTransformer() : nh_("~")
{
    std::string input_point_cloud_topic_name;
    std::string output_point_cloud_topic_name;
    
    nh_.param("input_point_cloud_topic_name", input_point_cloud_topic_name, std::string("/point_cloud"));
    nh_.param("output_point_cloud_topic_name", output_point_cloud_topic_name, std::string("/point_cloud_transformer/point_cloud"));
    nh_.param("output_point_cloud_parent_frame_id", output_point_cloud_parent_frame_id_, std::string("/map"));

    ros::Subscriber point_cloud_subscriber_ = nh_.subscribe(input_point_cloud_topic_name, 10, &PointCloudTransformer::pointCloudCallback, this);
    ros::Publisher point_cloud_publisher_ = nh_.advertise<sensor_msgs::PointCloud2>(output_point_cloud_topic_name, 10);
}

void PointCloudTransformer::pointCloudCallback(const sensor_msgs::PointCloud2ConstPtr& point_cloud_const_ptr)
{
    sensor_msgs::PointCloud2 transformed_point_cloud;
    pcl_ros::transformPointCloud(output_point_cloud_parent_frame_id_, *point_cloud_const_ptr, transformed_point_cloud, tl_);
    point_cloud_publisher_.publish(transformed_point_cloud);
}