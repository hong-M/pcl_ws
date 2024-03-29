#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>

main(int argc, char **argv)
{
    std::string pcdFileName;

    ros::init (argc, argv, "pcl_read");

    ros::NodeHandle nh;
    ros::NodeHandle n("~");
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_output", 1);

    n.param<std::string>("pcdFileName", pcdFileName, "test_pcd.pcd");
    ROS_INFO_STREAM("pcdFileName: "<< pcdFileName << " !");

    sensor_msgs::PointCloud2 output;
    pcl::PointCloud<pcl::PointXYZ> cloud;

    //pcl::io::loadPCDFile ("test_pcd.pcd", cloud);
    pcl::io::loadPCDFile (pcdFileName, cloud);

    pcl::toROSMsg(cloud, output);
    output.header.frame_id = "odom";

    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        pcl_pub.publish(output);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

