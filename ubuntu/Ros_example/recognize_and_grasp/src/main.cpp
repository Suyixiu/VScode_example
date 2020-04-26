#include "control.h"
#include "debug.h"
#include "recognize.h"

const string rgb_topic = "/kinect2/rgb/image_raw";
const string depth_topic = "/kinect2/depth/image_raw";

string RGBmask_dir = "/home/suyixiu/catkin_ws/src/yixiuge_ur/data/RGB_mask.png";
string Depthmask_dir = "/home/suyixiu/catkin_ws/src/yixiuge_ur/data/RGB_mask.png";

int main(int argc, char **argv)
{
    ros::init(argc, argv, "yixiuge_moveit");
    ROS_INFO("It's me you an asshole!\n");
    ros::NodeHandle nh;
    cv::startWindowThread();
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber rgb_sub = it.subscribe(rgb_topic, 1, rgb_Callback);
    image_transport::Subscriber depth_sub = it.subscribe(depth_topic, 1, depth_Callback);

    dynamic_reconfigure::Server<yixiuge_ur::dynamicConfig> server;
    dynamic_reconfigure::Server<yixiuge_ur::dynamicConfig>::CallbackType callback;

    callback = boost::bind(&dynamic_callback, _1);
    server.setCallback(callback);

    ros::AsyncSpinner spinner(4);
    spinner.start();

    ros::Rate loop_rate(1000); //设置发送数据的频率为1000Hz

    move(home, 0.0);

    Mat RGB_mask = imread("/home/suyixiu/catkin_ws/src/yixiuge_ur/data/RGB_mask.png",IMREAD_UNCHANGED);
    Mat Depth_mask = imread("/home/suyixiu/catkin_ws/src/yixiuge_ur/data/Depth_mask.png",IMREAD_UNCHANGED);

    while (ros::ok()) //ros::ok()返回false会停止运行，进程终止。
    {
        if (RGB_update_flag && Depth_update_flag)
        {
            RGB_update_flag = 0;
            Depth_update_flag = 0;
            imshow("rgb_img", RGB_img);
            imshow("depth_img", Depth_img);
            Point3f target_pos = recognize(RGB_mask, Depth_mask);
            waitKey(1);
            if (save_image_flag)
            {
                save_image_flag = false;
                static int image_index = 1;
                char text[20];
                sprintf(text, "/home/suyixiu/catkin_ws/src/yixiuge_ur/data/RGB_%d.png", image_index);
                imwrite(text, RGB_img);
                sprintf(text, "/home/suyixiu/catkin_ws/src/yixiuge_ur/data/Depth_%d.png", image_index);
                imwrite(text, Depth_img);
                ROS_INFO("save %d done \n", image_index);
                image_index++;
            }
            if (enable_move_obj_flag)
            {
                enable_move_obj_flag = false;
                move_obj(obj_name, obj_x, obj_y, obj_z, obj_roll, obj_pitch, obj_yaw);
                ROS_INFO("move obj done!\n");
            }
            if (enable_move_and_grasp_flag)
            {
                enable_move_and_grasp_flag = false;
                if(target_pos.z < -0.19)
                    target_pos.z = -0.19;
                ROS_INFO("x:%lf\ty:%lf\tz:%lf\n", target_pos.x, target_pos.y, target_pos.z);
                move(target_pos.x, target_pos.y, target_pos.z + 0.1, eelink_roll, eelink_pitch, eelink_yaw);
                move(target_pos.x, target_pos.y, target_pos.z, eelink_roll, eelink_pitch, eelink_yaw);
                grasp(grasp_angle);
                move(target_pos.x, target_pos.y, target_pos.z + 0.1, eelink_roll, eelink_pitch, eelink_yaw);
                grasp(0.8);
                move(home, 0.0);
                move_obj(obj_name, obj_x, obj_y, obj_z, 0, 0, 0);
                ROS_INFO("move_and_grasp done!\n");
                // ROS_INFO("x:%lf\ty:%lf\tz:%lf\n", eelink_x, eelink_y, eelink_z);
                // move(eelink_x, eelink_y, eelink_z + 0.1, eelink_roll, eelink_pitch, eelink_yaw);
                // move(eelink_x, eelink_y, eelink_z, eelink_roll, eelink_pitch, eelink_yaw);
                // grasp(grasp_angle);
                // move(eelink_x, eelink_y, eelink_z + 0.1, eelink_roll, eelink_pitch, eelink_yaw);
                // grasp(0.8);
                // move_obj(obj_name, obj_x, obj_y, obj_z, 0, 0, 0);
                // ROS_INFO("move_and_grasp done!\n");
            }
            if (enable_moveit_flag)
            {
                enable_moveit_flag = false;
                move(eelink_x, eelink_y, eelink_z, eelink_roll, eelink_pitch, eelink_yaw);
                ROS_INFO("moveit done!\n");
            }
            if (enable_grasp_flag)
            {
                enable_grasp_flag = false;
                grasp(grasp_angle);
                ROS_INFO("grasp done!\n");
            }
        }
        ros::spinOnce();   //不是必须，若程序中订阅话题则必须，否则回掉函数不起作用。
        loop_rate.sleep(); //按前面设置的10Hz频率将程序挂起
    }

    // move(0.75, 0.25, 0.0, eelink_roll, eelink_pitch, eelink_yaw);
    // move(0.75, 0.25, -0.19, eelink_roll, eelink_pitch, eelink_yaw);
    // grasp(0.32);
    // move(0.75, 0.25, 0.0, eelink_roll, eelink_pitch, eelink_yaw);
    // grasp(0.8);

    // ros::Duration(1).sleep();

    // move_obj("box", 0.75, 0.25, 0.964, 0, 0, 0); //抓完释放物体之后将物体归位
    // ros::shutdown();
    return 0;

}