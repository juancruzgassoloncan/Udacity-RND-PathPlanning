#!/bin/sh

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch 3d_sensor:=kinect" &
sleep 5
xterm -e " roslaunch rvizconfig rviz.launch " &
sleep 5
xterm -e "rosrun home_service home_service "

