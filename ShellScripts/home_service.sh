#!/bin/sh

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/robotica/PathPlanning/Udacity-RND-PathPlanning/src/World/MyUworld2.world " &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/robotica/PathPlanning/Udacity-RND-PathPlanning/src/World/Umap.yaml 3d_sensor:=kinect" &
sleep 5
xterm -e " rosrun rviz rviz -d /home/robotica/PathPlanning/RoboND-HomeServiceRobot-master/src/RvizConfig/home_service.rviz " &
sleep 5
xterm -e "rosrun home_service home_service "

