#!/usr/bin/env bash

source ~/catkin_ws/devel/setup.bash

export ROS_HOSTNAME=gigabyte
export ROS_MASTER_URI=http://satellite:11311
exec "$@"
