#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <yixiuge_ur/dynamicConfig.h>

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

#define pi 3.1415926

extern string obj_name;
extern double obj_x;
extern double obj_y;
extern double obj_z;
extern double obj_roll;
extern double obj_pitch;
extern double obj_yaw;
extern double eelink_x;
extern double eelink_y;
extern double eelink_z;
extern double eelink_roll;
extern double eelink_pitch;
extern double eelink_yaw;
extern double grasp_angle;
extern bool enable_move_and_grasp_flag;
extern bool enable_move_obj_flag;
extern bool enable_moveit_flag;
extern bool enable_grasp_flag;
extern bool save_image_flag;


void dynamic_callback(yixiuge_ur::dynamicConfig &config);

#endif