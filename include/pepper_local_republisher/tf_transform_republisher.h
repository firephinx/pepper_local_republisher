#ifndef _TF_TRANSFORM_REPUBLISHER_H
#define _TF_TRANSFORM_REPUBLISHER_H

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

class TFTransformRepublisher
{
    private:
        ros::NodeHandle nh_;
        tf::TransformBroadcaster tb_;
        tf::TransformListener tl_;

    public:
        TFTransformRepublisher();
        ~TFTransformRepublisher(){}
};


#endif