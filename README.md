# pepper_local_republisher

This ros package is used for republishing all of the Image and Point cloud topics from Pepper locally on a desktop to decrease the required wifi bandwidth for Pepper.

## Configuration Instructions
1. Modify the parameters in the launch/pepper_local_republisher.launch file to your liking.
2. You can modify the parameters in all of the launch files in order to test each node separately.

## Installation Instructions
1. Clone the perception_pcl repository located here: https://github.com/ros-perception/perception_pcl into the source folder of your catkin workspace.
2. Clone this repository into the source folder of your catkin workspace.
3. Build the ros packages using `catkin_make` in your catkin workspace.

## Usage Instructions
1. Source your `devel/setup.bash` in your catkin workspace.
2. Start the pepper_local_republisher with the command `roslaunch pepper_local_republisher pepper_local_republisher.launch`.