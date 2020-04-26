#ifndef _RECOGNIZE_H_
#define _RECOGNIZE_H_

#include <ros/ros.h>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include "std_msgs/String.h" //包含了使用的数据类型
#include "sensor_msgs/Image.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

#define pi 3.1415926
#define table_hight 0.996
#define velocity 1.0

extern Mat RGB_img, IR_img, Depth_img;
extern bool RGB_update_flag, IR_update_flag, Depth_update_flag;

void rgb_Callback(const sensor_msgs::ImageConstPtr &msg);
void depth_Callback(const sensor_msgs::ImageConstPtr &msg);

Point3f recognize(Mat RGB_mask, Mat Depth_mask);

#endif