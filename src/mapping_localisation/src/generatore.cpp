#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include<sensor_msgs/Imu.h>


class generatore_twist {

    sensor_msgs::Imu nuovo;

private:
    ros::NodeHandle n;
    ros::Subscriber sub1;
    ros::Publisher pub;

public:
    generatore_twist(){

        sub1 = n.subscribe("/mavros/imu/data_raw", 200, &generatore_twist::callback, this);
        pub = n.advertise<sensor_msgs::Imu>("/mavros/imu/data_raw_correct", 10);

        while (ros::ok()){
            ros::spin();
        }
    }


    void callback(const sensor_msgs::Imu::ConstPtr& msg){
        nuovo.header = msg->header;
        nuovo.orientation = msg->orientation;
        nuovo.angular_velocity = msg->angular_velocity;
        nuovo.angular_velocity_covariance = msg->angular_velocity_covariance;
        nuovo.linear_acceleration = msg->linear_acceleration;
        nuovo.linear_acceleration_covariance = msg->linear_acceleration_covariance;
        nuovo.header.frame_id = "/scout/base_link";
        pub.publish(nuovo);
    }

};

int main(int argc, char **argv){

    ros::init(argc, argv, "generatore_twist");
    generatore_twist my_generatore_twist;
    return 0;
}