#include <iostream>
#include <pcl/common/common_headers.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/console/parse.h>

using namespace std;

int main(int argc, char **argv)
{
    cout << "Test PCL !!!" << endl;
    cout << "argv[1] = " << argv[1] << endl;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile(argv[1], *cloud);

    for (size_t i = 0; i < cloud->points.size(); ++i)
        std::cout << "x:" << cloud->points[i].x << " "
                  << "y:" << cloud->points[i].y << " "
                  << "z:" << cloud->points[i].z << " " << std::endl;

    pcl::visualization::CloudViewer viewer("Cloud viewer");

    viewer.showCloud(cloud);

    std::cout << "Loaded " << cloud->width * cloud->height << " points " << std::endl;

    while (!viewer.wasStopped())
    {
    }

    return (0);
}