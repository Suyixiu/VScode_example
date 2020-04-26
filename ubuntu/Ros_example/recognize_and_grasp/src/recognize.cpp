#include "recognize.h"

Mat RGB_img, IR_img, Depth_img;
bool RGB_update_flag = 0, IR_update_flag = 0, Depth_update_flag = 0;

void rgb_Callback(const sensor_msgs::ImageConstPtr &msg)
{
	RGB_update_flag = 0;
	try
	{
		RGB_img = cv_bridge::toCvShare(msg, "bgr8")->image.clone();
		RGB_update_flag = 1;
		// cv::imshow("rgb_img", RGB_img);
		// cv::waitKey(1);
	}
	catch (cv_bridge::Exception &e)
	{
		ROS_ERROR("rgb Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
	}
}

void depth_Callback(const sensor_msgs::ImageConstPtr &msg)
{
	Depth_update_flag = 0;
	try
	{
		Mat Depth_img_32FC1 = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::TYPE_32FC1)->image.clone(); //得到的是32FC1的图片 对应type为5
		Depth_img_32FC1.convertTo(Depth_img, CV_16U, 65535.0 / 1.0, 0.0);
		Depth_update_flag = 1;
		// cv::imshow("depth_img", Depth_img);
		// Mat img_8UC1;
		// Depth_img.convertTo(img_8UC1, CV_8U, 255.0 / 65535, 0.0); //转成8UC1来addWeighted 对应type为0
		// Mat result;
		// Mat Channels[3] = {img_8UC1, img_8UC1, img_8UC1};
		// merge(Channels, 3, result); //merge成3通道的8UC3 对应type为16
		// addWeighted(result, 0.5, RGB_img, 0.5, 0.0, result);
		// cv::imshow("depth_result_img", result);
		// cv::waitKey(1);
	}
	catch (cv_bridge::Exception &e)
	{
		ROS_ERROR("depth Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
	}
}

/* 深度图配准到RGB图的矩阵 */
double mat_ir2rgb[] = {1.000070, -0.000001, -0.099105, -29.447156, 0.000109, 1.000041, -0.104798, 0.010875}; //乘上ir的uv索引出rgb的uv

/**
* @brief	深度图配准到RGB函数
* @param	Depth_img：原始深度图
* @param	dst：经过配准之后的深度图
* @param	w：深度图配准到RGB图的矩阵
* @note     原理是遍历深度图的每一个坐标然后通过配准矩阵映射到RGB中
*           然后把深度赋值过去 此外在映射失败像素点则用能重新映射上的点填上
*/
void Depth2RGB(cv::Mat &Depth_img, cv::Mat &dst, const double *W)
{
	double z;
	uint16_t u_ir, v_ir, d;
	uint16_t u_rgb, v_rgb;
	uint16_t u_rgb_old = 0;
	cv::Mat newdepth(Depth_img.rows, Depth_img.cols, CV_16UC1, cv::Scalar(0));
	// cv::Mat newdepth(dst.rows, dst.cols, CV_16UC1, cv::Scalar(0));
	static int count = 1;
	for (v_ir = 0; v_ir < Depth_img.rows; v_ir++)
	{
		for (u_ir = 0; u_ir < Depth_img.cols; u_ir++)
		{
			int type = Depth_img.type();
			d = Depth_img.at<uint16_t>(v_ir, u_ir);
			z = (double)d / 65535.0;
			u_rgb = (uint16_t)((W[0] * (double)u_ir + W[1] * (double)v_ir + W[2] + W[3] / z));
			v_rgb = (uint16_t)((W[4] * (double)u_ir + W[5] * (double)v_ir + W[6] + W[7] / z));

			if (u_rgb >= 0 && u_rgb <= newdepth.cols && v_rgb >= 0 && v_rgb <= newdepth.rows)
			{
				int delta = u_rgb - u_rgb_old - 1;
				if (delta > 0)
				{
					for (int i = 0; i < delta + 1; i++)
					{
						uint16_t *val = (uint16_t *)newdepth.ptr<uchar>(v_rgb) + u_rgb_old + i + 1;
						*val = d;
					}
					u_rgb_old = u_rgb;
				}
				else
				{
					uint16_t *val = (uint16_t *)newdepth.ptr<uchar>(v_rgb) + u_rgb;
					*val = d;
					u_rgb_old = u_rgb;
				}
			}
		}
	}
	dst = newdepth;
}

/**
* @brief	获取深度函数
* @param	u_rgb：深度图的横坐标
* @param	v_rgb：深度图的纵坐标
* @param	Depth_img：要获取深度的深度图
*/
double get_depth(uint16_t u_rgb, uint16_t v_rgb, cv::Mat &Depth_img)
{
	return Depth_img.at<uint16_t>(u_rgb, v_rgb) / 65535.0;
}

/* 手眼标定得到的转移关系 是眼坐标到手坐标的关系 */
double qw = 0.00018382306817985275;
double qx = 0.9999979321467403;
double qy = 0.001991707549965945;
double qz = -0.00036744027853962037;
double tx = 0.0005511244898617881;
double ty = 0.08023585460820704;
double tz = 0.12154307323658466;

Mat Quaternion = (cv::Mat_<float>(4, 1) << qw, qx, qy, qz);

/**
* @brief	四元数转成旋转矩阵函数
* @param	q：四元数
*/
Mat Quaternion2Matrix (cv::Mat q)
{
  float w = q.at<float>(0);
  float x = q.at<float>(1);
  float y = q.at<float>(2);
  float z = q.at<float>(3);

  float xx = x*x;
  float yy = y*y;
  float zz = z*z;
  float xy = x*y;
  float wz = w*z;
  float wy = w*y;
  float xz = x*z;
  float yz = y*z;
  float wx = w*x;

  float ret[4][4];
  ret[0][0] = 1.0f-2*(yy+zz);
  ret[0][1] = 2*(xy-wz);
  ret[0][2] = 2*(wy+xz);
  ret[0][3] = 0.0f;
 
  ret[1][0] = 2*(xy+wz);
  ret[1][1] = 1.0f-2*(xx+zz);
  ret[1][2] = 2*(yz-wx);
  ret[1][3] = 0.0f;
 
  ret[2][0] = 2*(xz-wy);
  ret[2][1] = 2*(yz+wx);
  ret[2][2] = 1.0f-2*(xx+yy);
  ret[2][3] = 0.0f;
 
  ret[3][0] = 0.0f;
  ret[3][1] = 0.0f;
  ret[3][2] = 0.0f;
  ret[3][3] = 1.0f;
 
  return cv::Mat(4,4,CV_32FC1,ret).clone();
}

/**
* @brief	获取相机坐标系下物体位置函数
* @param	picture_frame_pos：图像坐标系中的坐标点
* @param	z：该点的深度
* @note     得到的是4x1的矩阵
*/
Mat get_camra_frame_pos(Point picture_frame_pos, double z)
{
	double fx, fy, cx, cy, k1, k2, k3, p1, p2;
	fx = 589.3664541825391;
	fy = 589.3664541825391;
	cx = 320.5;
	cy = 240.5;
	k1 = 0;
	k2 = 0;
	k3 = 0;
	p1 = 0;
	p2 = 0;

	Mat cameraMatrix = (cv::Mat_<float>(3, 3) << fx, 0.0, cx,
						0.0, fy, cy,
						0.0, 0.0, 1.0);
	Mat distCoeffs = (cv::Mat_<float>(5, 1) << k1, k2, p1, p2, k3);

	Mat input_pos = (cv::Mat_<float>(3, 1) << picture_frame_pos.x, picture_frame_pos.y, 1.0);
	
	Mat camra_frame_pos_3x1 = cameraMatrix.inv() * z * input_pos;

	Mat camra_frame_pos_4x1 = (cv::Mat_<float>(4, 1) << camra_frame_pos_3x1.at<float>(0,0), 
														camra_frame_pos_3x1.at<float>(0,1), 
														camra_frame_pos_3x1.at<float>(0,2), 
														1.0);
	return camra_frame_pos_4x1;
}

void center_g(const vector<Point> contour, Point &center)
{
	Moments mu;
	mu = moments(contour, false);
	center.x = mu.m10 / mu.m00;
	center.y = mu.m01 / mu.m00;
}

Point3f recognize(Mat RGB_mask, Mat Depth_mask)
{
	Mat output(Depth_img.rows, Depth_img.cols, CV_16UC1, cv::Scalar(0)); //初始化配准的深度图
	Depth2RGB(Depth_img, output, mat_ir2rgb);                            //将输入的Depth_img根据转移矩阵配准成output
	cv::imshow("output", output);                                        //配准后的深度图

	/* 显示配准后的揉在一起的效果 */
	// Mat temp;
	// output.convertTo(temp, CV_8U, 255.0 / 65535.0, 0.0); //转成8UC1来addWeighted 对应type为0
	// Mat registration_result;
	// Mat new_Channels[3] = {temp, temp, temp};
	// merge(new_Channels, 3, registration_result); //merge成3通道的8UC3 对应type为16
	// addWeighted(registration_result, 0.5, RGB_img, 0.5, 0.0, registration_result);
	// cv::imshow("registration_result", registration_result);

	Mat RGB_diff = RGB_img - RGB_mask;
	imshow("RGB_diff", RGB_diff);
	Mat RGB_diff_threshold;
	threshold(RGB_diff, RGB_diff_threshold, 10, 255, THRESH_BINARY);
	imshow("RGB_diff_threshold", RGB_diff_threshold);

	Mat RGB_diff_gray;
	cvtColor(RGB_diff_threshold, RGB_diff_gray, CV_BGR2GRAY);
	vector<vector<Point> > contours;
	findContours(RGB_diff_gray, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	size_t contoursize = contours.size();
	size_t bigsize = 0, smallsize = 0;
	vector<Point> TheBiggest;
	int biggest_index = 0;
	for (size_t i = 0; i < contoursize; i++)
	{
		if (bigsize < contours[i].size())
		{
			bigsize = contours[i].size();
			TheBiggest = contours[i];
			biggest_index = i;
		}
	}
	Point target_pos;

	Mat show_result = RGB_img.clone();
	if (TheBiggest.size() > 0)
	{
		center_g(TheBiggest, target_pos);
		drawContours(show_result, contours, biggest_index, Scalar(255, 0, 255), 2);
		circle(show_result, target_pos, 3, Scalar(0, 255, 0), -1); //绘制圆心
		imshow("result", show_result);

		double target_pos_height = get_depth(target_pos.y, target_pos.x, output);

		// cout << target_pos_height << endl;
		// cout << target_pos << endl;

		Mat camra_frame_pos_4x1 = get_camra_frame_pos(target_pos, target_pos_height);

		// cout << camra_frame_pos_4x1 << endl;

		Mat R = Quaternion2Matrix(Quaternion);

		Mat T = (cv::Mat_<float>(4, 4) << 1.0, 0.0, 0.0, -tx,
				0.0, 1.0, 0.0, -ty,
				0.0, 0.0, 1.0, -tz,
				0.0, 0.0, 0.0, 1.0);

		Mat gripper_frame_pos_4x1 = R * T * camra_frame_pos_4x1;

		/* world_frame_pos_3x1是最终结果 因为每次都是回到home再去抓所以没有旋转 就很奈斯 */
		Mat world_frame_pos_3x1 = (cv::Mat_<float>(3, 1) << gripper_frame_pos_4x1.at<float>(0,0) - 0.11, 
														gripper_frame_pos_4x1.at<float>(0,1) + 0.67, 
														gripper_frame_pos_4x1.at<float>(0,2) + 0.093);

		Point3f result(world_frame_pos_3x1.at<float>(0, 0), world_frame_pos_3x1.at<float>(0, 1), world_frame_pos_3x1.at<float>(0, 2));
		return result;
	}
	else
	{
		return Point3f(-0.11,0.67,0.1);//没识别到就呆在home
	}
	
}