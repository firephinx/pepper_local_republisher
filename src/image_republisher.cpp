#include "pepper_local_republisher/image_republisher.h"

ImageRepublisher::ImageRepublisher() : nh_("~"), it_(nh_)
{
  std::string input_image_topic_name;
  std::string input_image_transport_type;
  std::string output_image_topic_name;

  nh_.param("input_image_topic_name", input_image_topic_name, std::string("/camera/raw"));
  nh_.param("input_image_transport_type", input_image_transport_type, std::string("raw"));
  nh_.param("output_image_topic_name", output_image_topic_name, std::string("/image_republisher/camera/raw"));
  nh_.param("output_image_frame_id_name", output_image_frame_id_name_, std::string(""));

  if(output_image_frame_id_name_.empty())
  {
    change_frame_id_ = false;
  }
  else
  {
    change_frame_id_ = true;
  }

  // Subscribe to input video feed and publish output video feed
  image_sub_ = it_.subscribe(input_image_topic_name, 1, &ImageRepublisher::republishImage, this, image_transport::TransportHints(input_image_transport_type));
  
  image_pub_ = it_.advertise(output_image_topic_name, 1);
}

void ImageRepublisher::republishImage(const sensor_msgs::ImageConstPtr& image_const_ptr_msg)
{
  if(change_frame_id_)
  {
    sensor_msgs::ImagePtr image_ptr_msg(new sensor_msgs::Image);
    image_ptr_msg->header.seq = image_const_ptr_msg->header.seq;
    image_ptr_msg->header.stamp = image_const_ptr_msg->header.stamp;

    // Change the frame_id of the message to the custom frame_id
    image_ptr_msg->header.frame_id = output_image_frame_id_name_;
    
    image_ptr_msg->height = image_const_ptr_msg->height;
    image_ptr_msg->width = image_const_ptr_msg->width;
    image_ptr_msg->encoding = image_const_ptr_msg->encoding;
    image_ptr_msg->is_bigendian = image_const_ptr_msg->is_bigendian;
    image_ptr_msg->step = image_const_ptr_msg->step;
    image_ptr_msg->data = image_const_ptr_msg->data;

    image_pub_.publish(image_ptr_msg);
  }
  else
  {
    // Publish original image message
    image_pub_.publish(image_const_ptr_msg);
  }
}