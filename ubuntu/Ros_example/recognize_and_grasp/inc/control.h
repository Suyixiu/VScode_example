#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <control_msgs/GripperCommandAction.h>
#include <control_msgs/GripperCommandGoal.h>
#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <tf/transform_broadcaster.h>
#include <gazebo_msgs/ModelState.h>
#include <geometry_msgs/Pose.h>
#include <gazebo_msgs/SetModelState.h>
#include <std_msgs/Bool.h>

#include "recognize.h"

#include <math.h>
#include <iostream>
#include <string>

#include <stdio.h>

using namespace std;

#define pi 3.1415926
#define table_hight 0.996
#define velocity 0.1

extern Point3f home;

void move(Point3f target_point, float yaw);
void move(float x, float y, float z, float roll, float pitch, float yaw);
void grasp(float angle);
void move_obj(string obj_name, float x, float y, float z, float roll, float pitch, float yaw);

#endif