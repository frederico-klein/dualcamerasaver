#!/usr/bin/env bash

export ROS_HOSTNAME=satellite
export ROS_MASTER_URI=http://gigabyte:11311

exec "$@"
