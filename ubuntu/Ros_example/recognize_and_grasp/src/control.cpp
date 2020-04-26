#include "control.h"

Point3f home(-0.11,0.67,0.1);

/**
* @brief	控制机械臂的move函数
* @param	x：从上往下看右边是x的正方向        ^ Y
* @param	y：从上往下看前边是y的正方向        |
* @param	z：从上往下看上边是z的正方向        + —— > X
* @param	roll：正中是0 具体需要角度自己看坐标轴旋转一下就知道了
* @param	pitch：正中是0 具体需要角度自己看坐标轴旋转一下就知道了
* @param	yaw：从上往下看 顺时针从左到右分别是-90 0 90
*/
void move(float x, float y, float z, float roll, float pitch, float yaw)
{
    moveit::planning_interface::MoveGroup group("yixiuge_ur5"); //ur5对应moveit中选择的规划部分

    geometry_msgs::Pose target_pose; //设置发送的数据，对应于moveit中的拖拽
    tf::Quaternion Q;

    roll = roll / 180.0 * pi;
    pitch = pitch / 180.0 * pi;
    yaw = yaw / 180.0 * pi;
    Q.setRPY(roll, pitch, yaw);
    target_pose.orientation.x = Q.getX();
    target_pose.orientation.y = Q.getY();
    target_pose.orientation.z = Q.getZ();
    target_pose.orientation.w = Q.getW();

    target_pose.position.x = x;
    target_pose.position.y = y;
    target_pose.position.z = z;

    group.setPoseTarget(target_pose);
    group.setMaxVelocityScalingFactor(velocity);

    moveit::planning_interface::MoveGroup::Plan my_plan; //进行运动规划，计算机器人移动到目标的运动轨迹，对应moveit中的plan按钮
    bool success = group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS;

    // ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

    if (success)
        group.execute(my_plan); //让机械臂按照规划的轨迹开始运动，对应moveit中的execute。
}

/**
* @brief	控制机械臂的move函数
* @param	target_point:目标点
* @param	yaw：从上往下看 顺时针从左到右分别是-90 0 90
*/
void move(Point3f target_point, float yaw)
{
    moveit::planning_interface::MoveGroup group("yixiuge_ur5"); //ur5对应moveit中选择的规划部分

    geometry_msgs::Pose target_pose; //设置发送的数据，对应于moveit中的拖拽
    tf::Quaternion Q;

    yaw = yaw / 180.0 * pi;
    Q.setRPY(0.0, 0.0, yaw);
    target_pose.orientation.x = Q.getX();
    target_pose.orientation.y = Q.getY();
    target_pose.orientation.z = Q.getZ();
    target_pose.orientation.w = Q.getW();

    target_pose.position.x = target_point.x;
    target_pose.position.y = target_point.y;
    target_pose.position.z = target_point.z;

    group.setPoseTarget(target_pose);
    group.setMaxVelocityScalingFactor(velocity);

    moveit::planning_interface::MoveGroup::Plan my_plan; //进行运动规划，计算机器人移动到目标的运动轨迹，对应moveit中的plan按钮
    bool success = group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS;

    // ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

    if (success)
        group.execute(my_plan); //让机械臂按照规划的轨迹开始运动，对应moveit中的execute。
}

void grasp(float angle)
{
    /* 抓取 */
    moveit::planning_interface::MoveGroup gripper_group("gripper");

    std::vector<double> rbq_joint_values;
    gripper_group.getCurrentState()->copyJointGroupPositions(gripper_group.getCurrentState()->getRobotModel()->getJointModelGroup(gripper_group.getName()), rbq_joint_values); // 通过设置关节值的方式。

    /* robotiq共有六个joint，只有设置gripper_finger1_joint才能生效，对应下面的rbq_joint_values[2] */
    rbq_joint_values[0] = 0;
    rbq_joint_values[1] = 0;
    rbq_joint_values[2] = 0.8f - angle; // your joint value
    rbq_joint_values[3] = 0;
    rbq_joint_values[4] = 0;
    rbq_joint_values[5] = 0;

    gripper_group.setJointValueTarget(rbq_joint_values);
    moveit::planning_interface::MoveGroup::Plan gripper_plan;
    bool grasp_flag = gripper_group.plan(gripper_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS;
    if (grasp_flag)
        gripper_group.execute(gripper_plan);
}

void move_obj(string obj_name, float x, float y, float z, float roll, float pitch, float yaw)
{
    ros::NodeHandle node_handle;
    ros::Publisher pub_update_flag = node_handle.advertise<std_msgs::Bool>("pos_update_flag", 1);
    ros::ServiceClient client = node_handle.serviceClient<gazebo_msgs::SetModelState>("/gazebo/set_model_state");
    gazebo_msgs::SetModelState set_model_state_srv;
    gazebo_msgs::ModelState des_model_state;
    geometry_msgs::Twist twist;

    twist.linear.x = 0.0;
    twist.linear.y = 0.0;
    twist.linear.z = 0.0;
    twist.angular.x = 0.0;
    twist.angular.y = 0.0;
    twist.angular.z = 0.0;

    geometry_msgs::Pose pose;
    geometry_msgs::Quaternion quat;

    tf::Quaternion Q;
    roll = roll / 180.0 * pi;
    pitch = pitch / 180.0 * pi;
    yaw = yaw / 180.0 * pi;
    Q.setRPY(roll, pitch, yaw);

    quat.x = Q.getX();
    quat.y = Q.getY();
    quat.z = Q.getZ();
    quat.w = Q.getW();

    pose.orientation = quat;
    pose.position.x = x;
    pose.position.y = y;
    pose.position.z = z;

    des_model_state.model_name = obj_name;
    des_model_state.pose = pose;
    des_model_state.twist = twist;
    des_model_state.reference_frame = "world";

    set_model_state_srv.request.model_state = des_model_state;
    client.call(set_model_state_srv);
    std_msgs::Bool flag;
    flag.data = true;
    pub_update_flag.publish(flag);
}
