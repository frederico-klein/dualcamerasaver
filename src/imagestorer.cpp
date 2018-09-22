#include "ros/ros.h"
#include <std_srvs/Empty.h>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <ctime>
using namespace std;
using namespace boost::filesystem;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "imagestorer");
  ros::NodeHandle n("~");
  //ros::ServiceClient client = n.serviceClient<std_srvs::Empty>("/imagesavernode/save");

  //get parameters

  std::string save_dir,store_dir;
  int num_images;
  n.getParam("save_dir", save_dir);
  ROS_INFO("Reading from directory: %s", save_dir.c_str());
  n.getParam("num_images", num_images);
  ROS_INFO("Number of images to move: %i", num_images);
  n.getParam("store_dir", store_dir);
  ROS_INFO("Storing into directory: %s", store_dir.c_str());
  float looprate;
  n.getParam("loop_rate", looprate);
  ROS_INFO("Looping rate %f", looprate);


  //std_srvs::Empty srv;
  //std::string path = "/path/to/directory";
  //for (auto & p : fs::directory_iterator(path))

  path p(save_dir);
  path storedir(store_dir);

  int imagecounter;
  ros::Rate loop_rate(looprate);
  //ros::Time mytime;
    /* okay, since i am saving only on this computer, there is
    no need to care about the ros server's time. it would be a problem if we
    were saving on multiple machines - which is not the case right now
    */

  while (ros::ok())
  {

    //slightly altered copypaste from stackexchange which is a copypaste from boosts docs
    imagecounter = 0;
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
    {
      ROS_DEBUG("Iterating through item %s",->path().string())
        if (!is_directory(i->path())&& !(i->path().extension().string().compare(".png"))) //we eliminate directories
        {
            //cout << i->path().filename().string() << " " <<  i->path().extension().string() << endl;
            imagecounter++;
        }
        else
            continue;
    }


    if (imagecounter>=num_images)
    {
      ROS_DEBUG("Moving images from %s to %s", save_dir.c_str(),store_dir.c_str() );
      try
      {
        //magic happens
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        std::string currtimestr = std::to_string(int(now->tm_year+1900)) +"_" +std::to_string(int(now->tm_mon+1))+"_"+std::to_string(now->tm_mday)+"_"+std::to_string(now->tm_hour)+"_"+std::to_string(now->tm_min)+"_"+std::to_string(now->tm_sec);
        for (auto i = directory_iterator(p); i != directory_iterator(); i++)
        {
            if (!is_directory(i->path())&& !(i->path().extension().string().compare(".png"))) //we eliminate directories
            {
                //cout << i->path().filename().string() << " " <<  i->path().extension().string() << endl;
                //mytime = ros::Time::now();

                std::string newname = i->path().filename().stem().string() + currtimestr + i->path().filename().extension().string();
                path newpathforthispng = storedir / newname;

                rename(i->path(),newpathforthispng);
            }
            else
                continue;
        }
      }
      catch (ros::Exception &e)
      {
        ROS_ERROR("Error occurred: %s", e.what());
      }
    }
    else
    {
      ROS_DEBUG("Got only %i images!",imagecounter);
      ROS_WARN_THROTTLE(10, "I can't seem to get enough images. Either limit %i images is incorrect for all publishing nodes, or some nodes are not publishing.",num_images);
    }
    ros::spinOnce();
  }


  return 0;
}
