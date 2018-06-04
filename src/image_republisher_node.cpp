#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

class ImageRepublisher
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

public:
  ImageRepublisher() : it_(nh_)
  {
    std::string input_image_topic_name;
    std::string output_image_topic_name;
    
    nh_.param("/image_republisher_node/input_image_topic_name", input_image_topic_name, std::string("/pepper_robot/camera/front/image_rect_color"));
    nh_.param("/image_republisher_node/output_image_topic_name", output_image_topic_name, std::string("/pepper_local_republisher/pepper_robot/camera/front/image_rect_color"));

    // Subscribe to input video feed and publish output video feed
    image_sub_ = it_.subscribe(input_image_topic_name, 1, &ImageRepublisher::republishImage, this);
    image_pub_ = it_.advertise(output_image_topic_name, 1);
  }

  ~ImageRepublisher()
  {
  }

  void republishImage(const sensor_msgs::ImageConstPtr& msg)
  {
    // Publish original image message
    image_pub_.publish(msg);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_republisher_node", ros::init_options::AnonymousName);
  ImageRepublisher ir;
  ros::spin();
  return 0;
}
