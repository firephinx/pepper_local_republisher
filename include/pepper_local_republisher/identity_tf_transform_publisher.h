#ifndef _IDENTITY_TF_TRANSFORM_PUBLISHER_H
#define _IDENTITY_TF_TRANSFORM_PUBLISHER_H

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

class IdentityTFTransformPublisher
{
    private:
        ros::NodeHandle nh_;
        tf::TransformBroadcaster tb_;

    public:
        IdentityTFTransformPublisher();
        ~IdentityTFTransformPublisher(){}
};


#endif