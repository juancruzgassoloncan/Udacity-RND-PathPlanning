#!/bin/sh

export TURTLEBOT_3D_SENSOR=kinect
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch " &  
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " & 
sleep 5
xterm  -e  " roslaunch turtlebot_navigation gmapping_demo.launch " &
sleep 5
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch "
