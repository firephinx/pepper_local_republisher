#ifndef _IMAGE_REPUBLISHER_H
#define _IMAGE_REPUBLISHER_H

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

class ImageRepublisher
{
  private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
    std::string output_image_frame_id_name_;
    bool change_frame_id_;

    void republishImage(const sensor_msgs::ImageConstPtr& image_const_ptr_msg);

  public:
  	ImageRepublisher();
  	~ImageRepublisher(){}
};

#endif